/***
>>>>> 重要说明：
	*
	*	1. FK750M4-XBT6 核心板 使用的是内部AXI SRAM作为显存，起始地址0x24000000，大小为512K
	*	2. 不管是单层显示还是双层显示，都不能超过 AXI SRAM 的大小
	*	3. 在刚下载完程序时，屏幕有轻微抖动和闪烁属于正常现象，等待片刻或者重新上电即可恢复正常
	* 	4. LTDC时钟在 main.c 文件里的 SystemClock_Config()函数设置，配置为10MHz，即刷新率在60帧左右，过高或者过低都会造成闪烁
	*	5. 受限于显存大小，开双层显示时，只能使用16位色格式
	* 
>>>>> 其他说明：
	*
	*	1. 中文字库使用的是小字库，即用到了对应的汉字再去取模，用户可以根据需求自行增添或删减
	*	2. 各个函数的功能和使用可以参考函数的说明以及 lcd_test.c 文件里的测试函数
	*
	*********************************************************************************************************************************************************************************************FANKE*****
***/

#include "lcd_rgb.h"

DMA2D_HandleTypeDef hdma2d;	// DMA2D句柄
LTDC_HandleTypeDef hltdc;		// LTDC句柄

/*************************************************************************************************
*	函 数 名:	HAL_LTDC_MspInit
*	入口参数:	无
*	返 回 值:	无
*	函数功能:	初始化LTDC引脚的IO口
*	说    明:	会被 HAL_LTDC_Init() 函数调用			
*************************************************************************************************/

void HAL_LTDC_MspInit(LTDC_HandleTypeDef* hltdc)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	if(hltdc->Instance==LTDC)
	{
		__HAL_RCC_LTDC_CLK_ENABLE();	// 使能LTDC时钟
		
		__HAL_RCC_GPIOK_CLK_ENABLE();	// 使能IO口时钟
		__HAL_RCC_GPIOJ_CLK_ENABLE();
		__HAL_RCC_GPIOI_CLK_ENABLE();

		GPIO_LDC_Backlight_CLK_ENABLE;	// 使能背光引脚IO口时钟

/*------------------------------LTDC GPIO Configuration--------------------------

    PJ12    ------> LTDC_B0			 PJ7     ------> LTDC_G0		 PI15    ------> LTDC_R0
    PJ13    ------> LTDC_B1          PJ8     ------> LTDC_G1       PJ0     ------> LTDC_R1	
    PJ14    ------> LTDC_B2	       PJ9     ------> LTDC_G2       PJ1     ------> LTDC_R2
    PJ15    ------> LTDC_B3	       PJ10    ------> LTDC_G3       PJ2     ------> LTDC_R3
    PK3     ------> LTDC_B4	       PJ11    ------> LTDC_G4       PJ3     ------> LTDC_R4
    PK4     ------> LTDC_B5          PK0     ------> LTDC_G5       PJ4     ------> LTDC_R5	
    PK5     ------> LTDC_B6          PK1     ------> LTDC_G6       PJ5     ------> LTDC_R6	
    PK6     ------> LTDC_B7	       PK2     ------> LTDC_G7       PJ6     ------> LTDC_R7	
	 
    PI14    ------> LTDC_CLK		
	 PK7     ------> LTDC_DE
    PI13    ------> LTDC_VSYNC	 
    PI12    ------> LTDC_HSYNC
	 
----------------------------------------------------------------------------------*/
	
		GPIO_InitStruct.Mode 		= GPIO_MODE_AF_PP;					// 复用输出模式
		GPIO_InitStruct.Pull 		= GPIO_NOPULL;							// 无上下拉
		GPIO_InitStruct.Speed 		= GPIO_SPEED_FREQ_VERY_HIGH;		// 速度等级
		GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;						// 复用线

		GPIO_InitStruct.Pin = GPIO_PIN_5|GPIO_PIN_4|GPIO_PIN_6|GPIO_PIN_3	
								  |GPIO_PIN_7|GPIO_PIN_2|GPIO_PIN_0|GPIO_PIN_1;	 
		HAL_GPIO_Init(GPIOK, &GPIO_InitStruct);		// 初始化 GPIOK 对应的LTDC引脚

		GPIO_InitStruct.Pin = GPIO_PIN_15|GPIO_PIN_14|GPIO_PIN_12|GPIO_PIN_13
								  |GPIO_PIN_11|GPIO_PIN_10|GPIO_PIN_9|GPIO_PIN_0
								  |GPIO_PIN_8|GPIO_PIN_7|GPIO_PIN_6|GPIO_PIN_1
								  |GPIO_PIN_5|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4;
		HAL_GPIO_Init(GPIOJ, &GPIO_InitStruct);		// 初始化 GPIOJ 对应的LTDC引脚

		GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
		HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);		// 初始化 GPIOI 对应的LTDC引脚


		// 初始化背光引脚
		GPIO_InitStruct.Pin 		= LCD_Backlight_PIN;				// 背光引脚
		GPIO_InitStruct.Mode 	= GPIO_MODE_OUTPUT_PP;			// 推挽输出模式
		GPIO_InitStruct.Pull 	= GPIO_NOPULL;						// 无上下拉
		GPIO_InitStruct.Speed 	= GPIO_SPEED_FREQ_LOW;			// 速度等级低
		HAL_GPIO_Init(LCD_Backlight_PORT, &GPIO_InitStruct);	// 初始化

		LCD_Backlight_OFF;	// 先关闭背光引脚，初始化之后再开启
	}
}


/*************************************************************************************************
*	函 数 名:	MX_LTDC_Init
*	入口参数:	无
*	返 回 值:	无
*	函数功能:	初始化LTDC引脚的IO口、全局参数、层设置等
*	说    明:	无			
*************************************************************************************************/

void MX_LTDC_Init(void)
{
	LTDC_LayerCfgTypeDef pLayerCfg = {0};		// layer0 相关参数
	__HAL_RCC_DMA2D_CLK_ENABLE();					// 使能DMA2D时钟

	hltdc.Instance 		 = LTDC;
	hltdc.Init.HSPolarity = LTDC_HSPOLARITY_AL;		// 低电平有效
	hltdc.Init.VSPolarity = LTDC_VSPOLARITY_AL;     // 低电平有效
	hltdc.Init.DEPolarity = LTDC_DEPOLARITY_AL;     // 低电平有效，要注意的是，很多面板都是高电平有效，但是750需要设置成低电平才能正常显示
	hltdc.Init.PCPolarity = LTDC_PCPOLARITY_IPC;    // 正常时钟信号
  
	hltdc.Init.HorizontalSync 		= HSW - 1;									// 根据屏幕设置参数即可
	hltdc.Init.VerticalSync 		= VSW	-1 ;
	hltdc.Init.AccumulatedHBP		= HBP + HSW -1;
	hltdc.Init.AccumulatedVBP 		= VBP + VSW -1;
	hltdc.Init.AccumulatedActiveW = LCD_Width  + HSW + HBP -1;
	hltdc.Init.AccumulatedActiveH = LCD_Height + VSW + VBP -1;
	hltdc.Init.TotalWidth 			= LCD_Width  + HSW + HBP + HFP - 1; 
	hltdc.Init.TotalHeigh 			= LCD_Height + VSW + VBP + VFP - 1;
	
	hltdc.Init.Backcolor.Red 		= 0;	// 初始背景色，R	
	hltdc.Init.Backcolor.Green 	= 0;  // 初始背景色，G	
	hltdc.Init.Backcolor.Blue 		= 0;	// 初始背景色，B
	
	HAL_LTDC_Init(&hltdc);	// 初始化LTDC参数

/*---------------------------------- layer0 显示配置 --------------------------------*/

	pLayerCfg.WindowX0 			= 0;										// 水平起点
	pLayerCfg.WindowX1 			= LCD_Width;							// 水平终点
	pLayerCfg.WindowY0 			= 0;										// 垂直起点
	pLayerCfg.WindowY1 			= LCD_Height;							// 垂直终点
	pLayerCfg.ImageWidth 		= LCD_Width;                     // 显示区域宽度
	pLayerCfg.ImageHeight 		= LCD_Height;                    // 显示区域高度	
	pLayerCfg.PixelFormat 		= ColorMode_0;							// 颜色格式	

// 配置 layer0 的恒定透明度，最终写入 LTDC_LxCACR 寄存器 
//	需要注意的是，这个参数是直接配置整个 layer0 的透明度，这里设置为255即不透明 
	pLayerCfg.Alpha 				= 255;									// 取值范围0~255，255表示不透明，0表示完全透明

// 设置 layer0 的层混合系数，最终写入 LTDC_LxBFCR 寄存器 
// 该参数用于设置 layer0 和 底层背景 之间的颜色混合系数，计算公式为 ：
// 混合后的颜色 =  BF1 * layer0的颜色 + BF2 * 底层背景的颜色
// 如果 layer0 使用了透明色，则必须配置成 LTDC_BLENDING_FACTOR1_PAxCA 和 LTDC_BLENDING_FACTOR2_PAxCA，否则ARGB中的A通道不起作用
//	更多的介绍可以查阅 参考手册关于 LTDC_LxBFCR 寄存器的介绍
	pLayerCfg.BlendingFactor1 	= LTDC_BLENDING_FACTOR1_CA;		// 混合系数1
	pLayerCfg.BlendingFactor2 	= LTDC_BLENDING_FACTOR2_CA;      // 混合系数2
	
// layer0 的显存地址，本例程使用750内部的AXI SRAM作为显存，起始地址0x24000000，大小为512K
// layer0 显存大小等于 = LCD_Width * LCD_Width * BytesPerPixel_0（每个像素所占字节大小）
// 因为 AXI SRAM 的大小只有512K，用户设置的区域一定不能超过这个值！	
	pLayerCfg.FBStartAdress 	= LCD_MemoryAdd;                 // 显存地址,使用750内部的AXI SRAM作为显存，地址0x24000000
	
	
// 配置 layer0 的初始默认颜色，包括A,R,G,B 的值 ，最终写入 LTDC_LxDCCR 寄存器 
	pLayerCfg.Alpha0 				= 0;			// 初始颜色，A
	pLayerCfg.Backcolor.Blue 	= 0;        //	初始颜色，R
	pLayerCfg.Backcolor.Green 	= 0;        //	初始颜色，G
	pLayerCfg.Backcolor.Red 	= 0;			//	初始颜色，B 
  
	HAL_LTDC_ConfigLayer(&hltdc, &pLayerCfg, 0);		// 配置layer0

#if ( ( ColorMode_0 == LTDC_PIXEL_FORMAT_RGB888 )||( ColorMode_0 == LTDC_PIXEL_FORMAT_ARGB8888 ) ) // 判断是否使用24位或者32位色

// 因为750每个通道的低位都是采用伪随机抖动输出，如果不开启颜色抖动，则无法正常显示24位或者32位色

	HAL_LTDC_EnableDither(&hltdc); // 开启颜色抖动
	
#endif


/*---------------------------------- layer1 显示配置 --------------------------------*/

#if ( LCD_NUM_LAYERS == 2 )	//如果定义了双层
  
	LTDC_LayerCfgTypeDef pLayerCfg1 = {0};
  
	pLayerCfg1.WindowX0 				= 0;							// 水平起点
	pLayerCfg1.WindowX1 				= LCD_Width;				// 水平终点
	pLayerCfg1.WindowY0 				= 0;							// 垂直起点
	pLayerCfg1.WindowY1 				= LCD_Height;				// 垂直终点
	pLayerCfg1.ImageWidth 			= LCD_Width;         	// 显示区域宽度
	pLayerCfg1.ImageHeight 			= LCD_Height;        	// 显示区域高度		
	pLayerCfg1.PixelFormat 			= ColorMode_1;				// 颜色格式，layer1 应配置为带有透明色的格式，例如ARGB8888或ARGB1555

// 配置 layer1 的恒定透明度，最终写入 LTDC_LxCACR 寄存器 
//	需要注意的是，这个参数是直接配置整个 layer1 的透明度，这里设置为255即不透明 
	pLayerCfg1.Alpha 					= 255;			// 取值范围0~255，255表示不透明，0表示完全透明
	
// 设置 layer1 的层混合系数，最终写入 LTDC_LxBFCR 寄存器 
// 该参数用于设置 layer1 和 (layer0+背景）之间的颜色混合系数，计算公式为 ：
// 混合后的颜色 =  BF1 * layer1的颜色 + BF2 * (layer0+背景混合后的颜色）
// 如果 layer1 使用了透明色，则必须配置成 LTDC_BLENDING_FACTOR1_PAxCA 和 LTDC_BLENDING_FACTOR2_PAxCA，否则ARGB中的A通道不起作用
//	更多的介绍可以查阅 参考手册关于 LTDC_LxBFCR 寄存器的介绍
	pLayerCfg1.BlendingFactor1 	= LTDC_BLENDING_FACTOR1_PAxCA;			// 混合系数1
	pLayerCfg1.BlendingFactor2 	= LTDC_BLENDING_FACTOR2_PAxCA;      	// 混合系数2
	
// layer1 的显存地址，本例程使用750内部的AXI SRAM作为显存，起始地址0x24000000，大小为512K
// 由于 layer0 会占用一部分显存，因此设置 layer1 显存时，需要进行一定偏移
// 因为 AXI SRAM 的大小只有512K，用户设置的区域一定不能超过这个值！
	pLayerCfg1.FBStartAdress 		= LCD_MemoryAdd + LCD_MemoryAdd_OFFSET; // 显存地址
	

// 配置layer1 的初始默认颜色，包括A,R,G,B 的值 ，最终写入 LTDC_LxDCCR 寄存器 
	pLayerCfg1.Alpha0 				= 0;				// 初始颜色，A
	pLayerCfg1.Backcolor.Red 		= 0;				//	初始颜色，R
	pLayerCfg1.Backcolor.Green 	= 0;           //	初始颜色，G
	pLayerCfg1.Backcolor.Blue 		= 0;           //	初始颜色，B 
	
	HAL_LTDC_ConfigLayer(&hltdc, &pLayerCfg1, 1);	// 初始化 layer1 的配置

	#if ( ( ColorMode_1 == LTDC_PIXEL_FORMAT_RGB888 )||( ColorMode_1 == LTDC_PIXEL_FORMAT_ARGB8888 ) ) // 判断是否使用24位或者32位色

	// 因为750每个通道的低位都是采用伪随机抖动输出，如果不开启颜色抖动，则无法正常显示24位或者32位色
		HAL_LTDC_EnableDither(&hltdc); // 开启颜色抖动
		
	#endif

#endif



// LTDC在初始化之后，上电的瞬间会有一个短暂的白屏，
//	即使一开始就将背光引脚拉低并且屏幕背光引脚用电阻下拉还是会有这个现象，
//	如果需要消除这个现象，可以在初始化完毕之后，进行一个短暂的延时再打开背光
//
//	HAL_Delay(200);	// 延时200ms

	LCD_Clear(0xff000000);	//	清屏为黑色
	LCD_Backlight_ON;			// 开启背光	
}

/***************************************************************************************************************
*	函 数 名:	LCD_Clear
*
*	函数功能:	清屏函数，将LCD清除为 color 的颜色，使用DMA2D实现
*
***************************************************************************************************************/

void LCD_Clear(uint32_t color)
{
	
	DMA2D->CR	  &=	~(DMA2D_CR_START);				//	停止DMA2D
	DMA2D->CR		=	DMA2D_R2M;							//	寄存器到SDRAM
	DMA2D->OPFCCR	=	ColorMode_0;						//	设置颜色格式
	DMA2D->OOR		=	0;										//	设置行偏移 
	DMA2D->OMAR		=	LCD_MemoryAdd ;					// 地址
	DMA2D->NLR		=	(LCD_Width<<16)|(LCD_Height);	//	设定长度和宽度
	
	DMA2D->OCOLR	=	color;							//	黑色
	

	DMA2D->CR	  |=	DMA2D_CR_START;					//	启动DMA2D
		
	while (DMA2D->CR & DMA2D_CR_START) ;				//	等待传输完成
	 
}

/***************************************************************************************************************************************
*	函 数 名: LCD_CopyBuffer
*
*	入口参数: x - 水平坐标，取值范围 0~479
*			 	 y - 垂直坐标，取值范围 0~271
*			 	 width  - 图片的水平宽度，最大取值480
*				 height - 图片的垂直宽度，最大取值272
*				 *color - 要复制的缓冲区地址
*				
*	函数功能: 在坐标 (x,y) 起始处复制缓冲区到显示区
*
*	说    明: 1. 使用DMA2D实现
*				 2. 要绘制的区域不能超过屏幕的显示区域
*				 3. 在 lv_port_disp.c 文件中，被函数 disp_flush() 调用，用以刷新显示区域		
* 			 4. 用阻塞态加载屏幕
*
*****************************************************************************************************************************************/

void LCD_CopyBuffer(uint16_t x, uint16_t y, uint16_t width, uint16_t height,uint32_t *color)
{

	DMA2D->CR	  &=	~(DMA2D_CR_START);				//	停止DMA2D
	DMA2D->CR		=	DMA2D_M2M;							//	存储器到存储器
	DMA2D->FGPFCCR	=	LTDC_PIXEL_FORMAT_RGB565;		//	设置颜色格式
   DMA2D->FGOR    =  0;										// 
	DMA2D->OOR		=	LCD_Width - width;				//	设置行偏移 	
	DMA2D->FGMAR   =  (uint32_t)color;		
	DMA2D->OMAR		=	LCD_MemoryAdd + BytesPerPixel_0*(LCD_Width * y + x);	// 地址;
	DMA2D->NLR		=	(width<<16)|(height);			//	设定长度和宽度		
	DMA2D->CR	  |=	DMA2D_CR_START;					//	启动DMA2D
		
	while (DMA2D->CR & DMA2D_CR_START) ;			//	等待传输完成

}

/**************************************************************************************************************************************************************************************************************************************************************************FANKE***/


