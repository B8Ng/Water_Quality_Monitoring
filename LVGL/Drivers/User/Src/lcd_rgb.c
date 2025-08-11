/***
>>>>> ��Ҫ˵����
	*
	*	1. FK750M4-XBT6 ���İ� ʹ�õ����ڲ�AXI SRAM��Ϊ�Դ棬��ʼ��ַ0x24000000����СΪ512K
	*	2. �����ǵ�����ʾ����˫����ʾ�������ܳ��� AXI SRAM �Ĵ�С
	*	3. �ڸ����������ʱ����Ļ����΢��������˸�����������󣬵ȴ�Ƭ�̻��������ϵ缴�ɻָ�����
	* 	4. LTDCʱ���� main.c �ļ���� SystemClock_Config()�������ã�����Ϊ10MHz����ˢ������60֡���ң����߻��߹��Ͷ��������˸
	*	5. �������Դ��С����˫����ʾʱ��ֻ��ʹ��16λɫ��ʽ
	* 
>>>>> ����˵����
	*
	*	1. �����ֿ�ʹ�õ���С�ֿ⣬���õ��˶�Ӧ�ĺ�����ȥȡģ���û����Ը����������������ɾ��
	*	2. ���������Ĺ��ܺ�ʹ�ÿ��Բο�������˵���Լ� lcd_test.c �ļ���Ĳ��Ժ���
	*
	*********************************************************************************************************************************************************************************************FANKE*****
***/

#include "lcd_rgb.h"

DMA2D_HandleTypeDef hdma2d;	// DMA2D���
LTDC_HandleTypeDef hltdc;		// LTDC���

/*************************************************************************************************
*	�� �� ��:	HAL_LTDC_MspInit
*	��ڲ���:	��
*	�� �� ֵ:	��
*	��������:	��ʼ��LTDC���ŵ�IO��
*	˵    ��:	�ᱻ HAL_LTDC_Init() ��������			
*************************************************************************************************/

void HAL_LTDC_MspInit(LTDC_HandleTypeDef* hltdc)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	if(hltdc->Instance==LTDC)
	{
		__HAL_RCC_LTDC_CLK_ENABLE();	// ʹ��LTDCʱ��
		
		__HAL_RCC_GPIOK_CLK_ENABLE();	// ʹ��IO��ʱ��
		__HAL_RCC_GPIOJ_CLK_ENABLE();
		__HAL_RCC_GPIOI_CLK_ENABLE();

		GPIO_LDC_Backlight_CLK_ENABLE;	// ʹ�ܱ�������IO��ʱ��

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
	
		GPIO_InitStruct.Mode 		= GPIO_MODE_AF_PP;					// �������ģʽ
		GPIO_InitStruct.Pull 		= GPIO_NOPULL;							// ��������
		GPIO_InitStruct.Speed 		= GPIO_SPEED_FREQ_VERY_HIGH;		// �ٶȵȼ�
		GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;						// ������

		GPIO_InitStruct.Pin = GPIO_PIN_5|GPIO_PIN_4|GPIO_PIN_6|GPIO_PIN_3	
								  |GPIO_PIN_7|GPIO_PIN_2|GPIO_PIN_0|GPIO_PIN_1;	 
		HAL_GPIO_Init(GPIOK, &GPIO_InitStruct);		// ��ʼ�� GPIOK ��Ӧ��LTDC����

		GPIO_InitStruct.Pin = GPIO_PIN_15|GPIO_PIN_14|GPIO_PIN_12|GPIO_PIN_13
								  |GPIO_PIN_11|GPIO_PIN_10|GPIO_PIN_9|GPIO_PIN_0
								  |GPIO_PIN_8|GPIO_PIN_7|GPIO_PIN_6|GPIO_PIN_1
								  |GPIO_PIN_5|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4;
		HAL_GPIO_Init(GPIOJ, &GPIO_InitStruct);		// ��ʼ�� GPIOJ ��Ӧ��LTDC����

		GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
		HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);		// ��ʼ�� GPIOI ��Ӧ��LTDC����


		// ��ʼ����������
		GPIO_InitStruct.Pin 		= LCD_Backlight_PIN;				// ��������
		GPIO_InitStruct.Mode 	= GPIO_MODE_OUTPUT_PP;			// �������ģʽ
		GPIO_InitStruct.Pull 	= GPIO_NOPULL;						// ��������
		GPIO_InitStruct.Speed 	= GPIO_SPEED_FREQ_LOW;			// �ٶȵȼ���
		HAL_GPIO_Init(LCD_Backlight_PORT, &GPIO_InitStruct);	// ��ʼ��

		LCD_Backlight_OFF;	// �ȹرձ������ţ���ʼ��֮���ٿ���
	}
}


/*************************************************************************************************
*	�� �� ��:	MX_LTDC_Init
*	��ڲ���:	��
*	�� �� ֵ:	��
*	��������:	��ʼ��LTDC���ŵ�IO�ڡ�ȫ�ֲ����������õ�
*	˵    ��:	��			
*************************************************************************************************/

void MX_LTDC_Init(void)
{
	LTDC_LayerCfgTypeDef pLayerCfg = {0};		// layer0 ��ز���
	__HAL_RCC_DMA2D_CLK_ENABLE();					// ʹ��DMA2Dʱ��

	hltdc.Instance 		 = LTDC;
	hltdc.Init.HSPolarity = LTDC_HSPOLARITY_AL;		// �͵�ƽ��Ч
	hltdc.Init.VSPolarity = LTDC_VSPOLARITY_AL;     // �͵�ƽ��Ч
	hltdc.Init.DEPolarity = LTDC_DEPOLARITY_AL;     // �͵�ƽ��Ч��Ҫע����ǣ��ܶ���嶼�Ǹߵ�ƽ��Ч������750��Ҫ���óɵ͵�ƽ����������ʾ
	hltdc.Init.PCPolarity = LTDC_PCPOLARITY_IPC;    // ����ʱ���ź�
  
	hltdc.Init.HorizontalSync 		= HSW - 1;									// ������Ļ���ò�������
	hltdc.Init.VerticalSync 		= VSW	-1 ;
	hltdc.Init.AccumulatedHBP		= HBP + HSW -1;
	hltdc.Init.AccumulatedVBP 		= VBP + VSW -1;
	hltdc.Init.AccumulatedActiveW = LCD_Width  + HSW + HBP -1;
	hltdc.Init.AccumulatedActiveH = LCD_Height + VSW + VBP -1;
	hltdc.Init.TotalWidth 			= LCD_Width  + HSW + HBP + HFP - 1; 
	hltdc.Init.TotalHeigh 			= LCD_Height + VSW + VBP + VFP - 1;
	
	hltdc.Init.Backcolor.Red 		= 0;	// ��ʼ����ɫ��R	
	hltdc.Init.Backcolor.Green 	= 0;  // ��ʼ����ɫ��G	
	hltdc.Init.Backcolor.Blue 		= 0;	// ��ʼ����ɫ��B
	
	HAL_LTDC_Init(&hltdc);	// ��ʼ��LTDC����

/*---------------------------------- layer0 ��ʾ���� --------------------------------*/

	pLayerCfg.WindowX0 			= 0;										// ˮƽ���
	pLayerCfg.WindowX1 			= LCD_Width;							// ˮƽ�յ�
	pLayerCfg.WindowY0 			= 0;										// ��ֱ���
	pLayerCfg.WindowY1 			= LCD_Height;							// ��ֱ�յ�
	pLayerCfg.ImageWidth 		= LCD_Width;                     // ��ʾ������
	pLayerCfg.ImageHeight 		= LCD_Height;                    // ��ʾ����߶�	
	pLayerCfg.PixelFormat 		= ColorMode_0;							// ��ɫ��ʽ	

// ���� layer0 �ĺ㶨͸���ȣ�����д�� LTDC_LxCACR �Ĵ��� 
//	��Ҫע����ǣ����������ֱ���������� layer0 ��͸���ȣ���������Ϊ255����͸�� 
	pLayerCfg.Alpha 				= 255;									// ȡֵ��Χ0~255��255��ʾ��͸����0��ʾ��ȫ͸��

// ���� layer0 �Ĳ���ϵ��������д�� LTDC_LxBFCR �Ĵ��� 
// �ò����������� layer0 �� �ײ㱳�� ֮�����ɫ���ϵ�������㹫ʽΪ ��
// ��Ϻ����ɫ =  BF1 * layer0����ɫ + BF2 * �ײ㱳������ɫ
// ��� layer0 ʹ����͸��ɫ����������ó� LTDC_BLENDING_FACTOR1_PAxCA �� LTDC_BLENDING_FACTOR2_PAxCA������ARGB�е�Aͨ����������
//	����Ľ��ܿ��Բ��� �ο��ֲ���� LTDC_LxBFCR �Ĵ����Ľ���
	pLayerCfg.BlendingFactor1 	= LTDC_BLENDING_FACTOR1_CA;		// ���ϵ��1
	pLayerCfg.BlendingFactor2 	= LTDC_BLENDING_FACTOR2_CA;      // ���ϵ��2
	
// layer0 ���Դ��ַ��������ʹ��750�ڲ���AXI SRAM��Ϊ�Դ棬��ʼ��ַ0x24000000����СΪ512K
// layer0 �Դ��С���� = LCD_Width * LCD_Width * BytesPerPixel_0��ÿ��������ռ�ֽڴ�С��
// ��Ϊ AXI SRAM �Ĵ�Сֻ��512K���û����õ�����һ�����ܳ������ֵ��	
	pLayerCfg.FBStartAdress 	= LCD_MemoryAdd;                 // �Դ��ַ,ʹ��750�ڲ���AXI SRAM��Ϊ�Դ棬��ַ0x24000000
	
	
// ���� layer0 �ĳ�ʼĬ����ɫ������A,R,G,B ��ֵ ������д�� LTDC_LxDCCR �Ĵ��� 
	pLayerCfg.Alpha0 				= 0;			// ��ʼ��ɫ��A
	pLayerCfg.Backcolor.Blue 	= 0;        //	��ʼ��ɫ��R
	pLayerCfg.Backcolor.Green 	= 0;        //	��ʼ��ɫ��G
	pLayerCfg.Backcolor.Red 	= 0;			//	��ʼ��ɫ��B 
  
	HAL_LTDC_ConfigLayer(&hltdc, &pLayerCfg, 0);		// ����layer0

#if ( ( ColorMode_0 == LTDC_PIXEL_FORMAT_RGB888 )||( ColorMode_0 == LTDC_PIXEL_FORMAT_ARGB8888 ) ) // �ж��Ƿ�ʹ��24λ����32λɫ

// ��Ϊ750ÿ��ͨ���ĵ�λ���ǲ���α�����������������������ɫ���������޷�������ʾ24λ����32λɫ

	HAL_LTDC_EnableDither(&hltdc); // ������ɫ����
	
#endif


/*---------------------------------- layer1 ��ʾ���� --------------------------------*/

#if ( LCD_NUM_LAYERS == 2 )	//���������˫��
  
	LTDC_LayerCfgTypeDef pLayerCfg1 = {0};
  
	pLayerCfg1.WindowX0 				= 0;							// ˮƽ���
	pLayerCfg1.WindowX1 				= LCD_Width;				// ˮƽ�յ�
	pLayerCfg1.WindowY0 				= 0;							// ��ֱ���
	pLayerCfg1.WindowY1 				= LCD_Height;				// ��ֱ�յ�
	pLayerCfg1.ImageWidth 			= LCD_Width;         	// ��ʾ������
	pLayerCfg1.ImageHeight 			= LCD_Height;        	// ��ʾ����߶�		
	pLayerCfg1.PixelFormat 			= ColorMode_1;				// ��ɫ��ʽ��layer1 Ӧ����Ϊ����͸��ɫ�ĸ�ʽ������ARGB8888��ARGB1555

// ���� layer1 �ĺ㶨͸���ȣ�����д�� LTDC_LxCACR �Ĵ��� 
//	��Ҫע����ǣ����������ֱ���������� layer1 ��͸���ȣ���������Ϊ255����͸�� 
	pLayerCfg1.Alpha 					= 255;			// ȡֵ��Χ0~255��255��ʾ��͸����0��ʾ��ȫ͸��
	
// ���� layer1 �Ĳ���ϵ��������д�� LTDC_LxBFCR �Ĵ��� 
// �ò����������� layer1 �� (layer0+������֮�����ɫ���ϵ�������㹫ʽΪ ��
// ��Ϻ����ɫ =  BF1 * layer1����ɫ + BF2 * (layer0+������Ϻ����ɫ��
// ��� layer1 ʹ����͸��ɫ����������ó� LTDC_BLENDING_FACTOR1_PAxCA �� LTDC_BLENDING_FACTOR2_PAxCA������ARGB�е�Aͨ����������
//	����Ľ��ܿ��Բ��� �ο��ֲ���� LTDC_LxBFCR �Ĵ����Ľ���
	pLayerCfg1.BlendingFactor1 	= LTDC_BLENDING_FACTOR1_PAxCA;			// ���ϵ��1
	pLayerCfg1.BlendingFactor2 	= LTDC_BLENDING_FACTOR2_PAxCA;      	// ���ϵ��2
	
// layer1 ���Դ��ַ��������ʹ��750�ڲ���AXI SRAM��Ϊ�Դ棬��ʼ��ַ0x24000000����СΪ512K
// ���� layer0 ��ռ��һ�����Դ棬������� layer1 �Դ�ʱ����Ҫ����һ��ƫ��
// ��Ϊ AXI SRAM �Ĵ�Сֻ��512K���û����õ�����һ�����ܳ������ֵ��
	pLayerCfg1.FBStartAdress 		= LCD_MemoryAdd + LCD_MemoryAdd_OFFSET; // �Դ��ַ
	

// ����layer1 �ĳ�ʼĬ����ɫ������A,R,G,B ��ֵ ������д�� LTDC_LxDCCR �Ĵ��� 
	pLayerCfg1.Alpha0 				= 0;				// ��ʼ��ɫ��A
	pLayerCfg1.Backcolor.Red 		= 0;				//	��ʼ��ɫ��R
	pLayerCfg1.Backcolor.Green 	= 0;           //	��ʼ��ɫ��G
	pLayerCfg1.Backcolor.Blue 		= 0;           //	��ʼ��ɫ��B 
	
	HAL_LTDC_ConfigLayer(&hltdc, &pLayerCfg1, 1);	// ��ʼ�� layer1 ������

	#if ( ( ColorMode_1 == LTDC_PIXEL_FORMAT_RGB888 )||( ColorMode_1 == LTDC_PIXEL_FORMAT_ARGB8888 ) ) // �ж��Ƿ�ʹ��24λ����32λɫ

	// ��Ϊ750ÿ��ͨ���ĵ�λ���ǲ���α�����������������������ɫ���������޷�������ʾ24λ����32λɫ
		HAL_LTDC_EnableDither(&hltdc); // ������ɫ����
		
	#endif

#endif



// LTDC�ڳ�ʼ��֮���ϵ��˲�����һ�����ݵİ�����
//	��ʹһ��ʼ�ͽ������������Ͳ�����Ļ���������õ����������ǻ����������
//	�����Ҫ����������󣬿����ڳ�ʼ�����֮�󣬽���һ�����ݵ���ʱ�ٴ򿪱���
//
//	HAL_Delay(200);	// ��ʱ200ms

	LCD_Clear(0xff000000);	//	����Ϊ��ɫ
	LCD_Backlight_ON;			// ��������	
}

/***************************************************************************************************************
*	�� �� ��:	LCD_Clear
*
*	��������:	������������LCD���Ϊ color ����ɫ��ʹ��DMA2Dʵ��
*
***************************************************************************************************************/

void LCD_Clear(uint32_t color)
{
	
	DMA2D->CR	  &=	~(DMA2D_CR_START);				//	ֹͣDMA2D
	DMA2D->CR		=	DMA2D_R2M;							//	�Ĵ�����SDRAM
	DMA2D->OPFCCR	=	ColorMode_0;						//	������ɫ��ʽ
	DMA2D->OOR		=	0;										//	������ƫ�� 
	DMA2D->OMAR		=	LCD_MemoryAdd ;					// ��ַ
	DMA2D->NLR		=	(LCD_Width<<16)|(LCD_Height);	//	�趨���ȺͿ��
	
	DMA2D->OCOLR	=	color;							//	��ɫ
	

	DMA2D->CR	  |=	DMA2D_CR_START;					//	����DMA2D
		
	while (DMA2D->CR & DMA2D_CR_START) ;				//	�ȴ��������
	 
}

/***************************************************************************************************************************************
*	�� �� ��: LCD_CopyBuffer
*
*	��ڲ���: x - ˮƽ���꣬ȡֵ��Χ 0~479
*			 	 y - ��ֱ���꣬ȡֵ��Χ 0~271
*			 	 width  - ͼƬ��ˮƽ��ȣ����ȡֵ480
*				 height - ͼƬ�Ĵ�ֱ��ȣ����ȡֵ272
*				 *color - Ҫ���ƵĻ�������ַ
*				
*	��������: ������ (x,y) ��ʼ�����ƻ���������ʾ��
*
*	˵    ��: 1. ʹ��DMA2Dʵ��
*				 2. Ҫ���Ƶ������ܳ�����Ļ����ʾ����
*				 3. �� lv_port_disp.c �ļ��У������� disp_flush() ���ã�����ˢ����ʾ����		
* 			 4. ������̬������Ļ
*
*****************************************************************************************************************************************/

void LCD_CopyBuffer(uint16_t x, uint16_t y, uint16_t width, uint16_t height,uint32_t *color)
{

	DMA2D->CR	  &=	~(DMA2D_CR_START);				//	ֹͣDMA2D
	DMA2D->CR		=	DMA2D_M2M;							//	�洢�����洢��
	DMA2D->FGPFCCR	=	LTDC_PIXEL_FORMAT_RGB565;		//	������ɫ��ʽ
   DMA2D->FGOR    =  0;										// 
	DMA2D->OOR		=	LCD_Width - width;				//	������ƫ�� 	
	DMA2D->FGMAR   =  (uint32_t)color;		
	DMA2D->OMAR		=	LCD_MemoryAdd + BytesPerPixel_0*(LCD_Width * y + x);	// ��ַ;
	DMA2D->NLR		=	(width<<16)|(height);			//	�趨���ȺͿ��		
	DMA2D->CR	  |=	DMA2D_CR_START;					//	����DMA2D
		
	while (DMA2D->CR & DMA2D_CR_START) ;			//	�ȴ��������

}

/**************************************************************************************************************************************************************************************************************************************************************************FANKE***/


