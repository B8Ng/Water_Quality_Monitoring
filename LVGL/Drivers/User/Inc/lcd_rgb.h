#ifndef  __LCD_RGB_H
#define	__LCD_RGB_H

#include "stm32h7xx_hal.h"


// 1. 如果只用单层，该参数定义为1即可，使用双层的话，需要修改为 2
// 2. FK750M4-XBT6 核心板 使用的是内部AXI SRAM作为显存，起始地址0x24000000，大小为512K
// 3. 显存所需空间 = 分辨率 * 每个像素所占字节数，例如 480*272的屏，使用16位色（RGB565或者AEGB1555），需要显存 480*272*2 = 261120 字节
// 4. 不管是单层显示还是双层显示，都不能超过 AXI SRAM 的大小
//	5. 如果用户需要双层显示，则只能设置 ARGB1555 + RGB565 或者 ARGB4444 + RGB565 的格式，两层所需显存为 480*272*2*2 = 522240 字节
//
#define 	LCD_NUM_LAYERS  1	//	定义显示的层数，750可驱动两层显示


#define	ColorMode_0   LTDC_PIXEL_FORMAT_RGB565   		//定义 layer0 的颜色格式
//#define	ColorMode_0   LTDC_PIXEL_FORMAT_ARGB1555  
//#define	ColorMode_0    LTDC_PIXEL_FORMAT_ARGB4444  
//#define	ColorMode_0   LTDC_PIXEL_FORMAT_RGB888
//#define	ColorMode_0   LTDC_PIXEL_FORMAT_ARGB8888   

#if  LCD_NUM_LAYERS == 2	// 如果开启了双层，则在此处定义 layer1 的颜色格式			

//	#define	ColorMode_1    LTDC_PIXEL_FORMAT_ARGB1555  // ARGB1555仅支持一位透明色，即仅有透明和不透明两种状态
	#define	ColorMode_1    LTDC_PIXEL_FORMAT_ARGB4444  // ARGB4444支持4位透明色，有16种透明状态
		
#endif

/*---------------------------------------------------------- 函数声明 -------------------------------------------------------*/
	
void 	MX_LTDC_Init(void);		// LTDC以及层初始化 
void  LCD_Clear(uint32_t color);			// 清屏函数

void  LCD_CopyBuffer(uint16_t x, uint16_t y, uint16_t width, uint16_t height,uint32_t *color);	// 复制缓冲区到显示区


/*-------------------------------------------------------- LCD相关参数 -------------------------------------------------------*/

#define HBP  43	// 根据屏幕的手册进行设置
#define VBP  12
#define HSW  1
#define VSW  1
#define HFP  8
#define VFP  8

#define LCD_Width     	480				//	LCD的像素长度
#define LCD_Height    	272				//	LCD的像素宽度
#define LCD_MemoryAdd   0x24000000 		//	显存的起始地址  

// layer0 每个像素所占字节

#if ( ColorMode_0 == LTDC_PIXEL_FORMAT_RGB565 || ColorMode_0 == LTDC_PIXEL_FORMAT_ARGB1555 || ColorMode_0 ==LTDC_PIXEL_FORMAT_ARGB4444 )
	#define BytesPerPixel_0		2		//16位色模式每个像素占2字节
#elif ColorMode_0 == LTDC_PIXEL_FORMAT_RGB888
	#define BytesPerPixel_0		3		//24位色模式每个像素占3字节
#else
	#define BytesPerPixel_0		4		//32位色模式每个像素占4字节
#endif	

// layer1 每个像素所占字节 

#if LCD_NUM_LAYERS == 2

	#if ( ColorMode_1 == LTDC_PIXEL_FORMAT_RGB565 || ColorMode_1 == LTDC_PIXEL_FORMAT_ARGB1555 || LTDC_PIXEL_FORMAT_ARGB4444)
		#define BytesPerPixel_1		2		//16位色模式每个像素占2字节
	#endif	
	
	#define LCD_MemoryAdd_OFFSET   LCD_Width * LCD_Height * BytesPerPixel_0 	 //第二层的显存的偏移地址 

#endif

/*-------------------------------------------------------- LCD背光引脚 -------------------------------------------------------*/

#define  LCD_Backlight_PIN								GPIO_PIN_2								
#define	LCD_Backlight_PORT							GPIOI									
#define 	GPIO_LDC_Backlight_CLK_ENABLE        	__HAL_RCC_GPIOI_CLK_ENABLE()	 	

#define	LCD_Backlight_OFF		HAL_GPIO_WritePin(LCD_Backlight_PORT, LCD_Backlight_PIN, GPIO_PIN_RESET);	// 关闭背光
#define 	LCD_Backlight_ON		HAL_GPIO_WritePin(LCD_Backlight_PORT, LCD_Backlight_PIN, GPIO_PIN_SET);		// 开启背光



#endif //__LCD_RGB_H

