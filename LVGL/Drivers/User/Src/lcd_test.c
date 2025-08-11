/***
	***************************************************************************************************************************
	*	@file  	lcd_test.c
	*	@version V1.0
	*  @date    2022-3-3
	*	@author  反客科技
	*	@brief   LTDC测试函数	
   ***************************************************************************************************************************
   *  @description
	*
	*	实验平台：反客STM32H750XBH6核心板 （型号：FK750M4-XBH6） + 4.3寸RGB液晶屏(屏幕型号RGB043M1-480*272)
	*	淘宝地址：https://shop212360197.taobao.com
	*	QQ交流群：536665479
	*
>>>>> 文件说明：
	*
	*	1. 仅用于测试，该文件不是必须，用户移植的时候可以舍弃
	*
	****************************************************************************************************************************
***/


#include "lcd_test.h"

/*************************************************************************************************
*	函 数 名:	LCD_Test_DoubleLayer
*
*	函数功能:	双层显示
*
*	说    明:	仅开启双层的时候生效			
*************************************************************************************************/

void LCD_Test_DoubleLayer(void)
{
	uint16_t time = 100;	// 延时时间
	uint8_t	i = 0;			// 计数变量
	
// 绘制初始界面，包括标题、LOGO以及进度条>>>>>
	
	LCD_SetBackColor(0xffB9EDF8); 			//	设置背景色，使用自定义颜色
	LCD_Clear(); 									//	清屏，刷背景色
	
	LCD_SetTextFont(&CH_Font32);				// 设置3232中文字体,ASCII字体对应为3216
	LCD_SetColor(0xff333333);					//	设置画笔色，使用自定义颜色
	LCD_DisplayText(176, 87,"双层测试");	// 显示文本
	
	LCD_SetColor(0xfffd7923);					//	设置画笔色，使用自定义颜色
	LCD_DrawImage(  120, 120, 240, 83, Image_FANKE_240x83) ;		// 显示LOGO图片

	LCD_SetColor(0xff003366);					//	设置画笔色，使用自定义颜色	
	for(i=0;i<100;i++)
   {
		LCD_FillRect(44,228,4*i,6);	// 绘制矩形，实现简易进度条的效果
		HAL_Delay(15);	
   }	
	
	
	LCD_SetLayer(1);	//切换到层1
	LCD_SetBackColor(LCD_BLACK & 0x00FFFFFF);  // 透明度100%，高8位的数字越小透明度越高
	LCD_Clear();										 // 此时前景层完全透明，否则无法看到 layer0 的图像	
	
// layer0 显示内容 >>>>>
		
	LCD_SetLayer(0);		//切换到层0	

	LCD_SetBackColor(LCD_BLACK);   
	LCD_Clear();
	
	LCD_SetColor(LCD_WHITE);	
	LCD_SetTextFont(&CH_Font24);				// 设置2424中文字体,ASCII字体对应为2412
	LCD_DisplayText(10,10,"STM32H750 LTDC 背景层，layer0"); 

	HAL_Delay(1000);
	
	LCD_SetColor(LIGHT_CYAN);  	LCD_DrawLine(5, 75,200, 75);	 	HAL_Delay(time);
	LCD_SetColor(LIGHT_MAGENTA);	LCD_DrawLine(5, 90,200, 90);   	HAL_Delay(time);
	LCD_SetColor(LIGHT_YELLOW); 	LCD_DrawLine(5,105,200,105);	 	HAL_Delay(time);
	
	LCD_SetColor(LCD_RED);    		LCD_FillCircle( 60,200,60);		HAL_Delay(time);
	LCD_SetColor(LCD_GREEN);  		LCD_FillCircle(100,200,60); 	   HAL_Delay(time);
	LCD_SetColor(LCD_BLUE);   		LCD_FillCircle(140,200,60);  		HAL_Delay(time);
	
	LCD_SetColor(LIGHT_RED);	  	LCD_FillRect(246, 65,125,120);	HAL_Delay(time);	  
	LCD_SetColor(LIGHT_GREEN);  	LCD_FillRect(293, 96,125,120);  	HAL_Delay(time);  
	LCD_SetColor(LIGHT_BLUE);    	LCD_FillRect(334,130,125,120);  	HAL_Delay(time);
	
	HAL_Delay(1000);
	
// layer1 显示内容 >>>>>

	LCD_SetLayer(1);	//切换到层1

	LCD_SetColor(0Xff348498);		
	LCD_FillRect(62, 48,322,192);		  

	LCD_SetBackColor(0Xff348498);  
	LCD_SetColor(LCD_BLACK);		
	LCD_DisplayText(146,69,"前景层，layer1"); 
	HAL_Delay(1000);
	
#if	ColorMode_1 == LTDC_PIXEL_FORMAT_ARGB4444	// 如果layer1 定义为 ARGB4444

	LCD_SetBackColor(LCD_BLACK & 0xB0FFFFFF);  // 设置背景色透明度，高8位的数字越小透明度越高，ARGB4444支持4位透明色，有16种透明状态
	LCD_SetColor(LCD_WHITE);						 // 画笔不透明 
	LCD_DisplayText(28,100,"STM32H750XBH6 LTDC, ARGB4444，layer1"); 
	HAL_Delay(1000);
	
	LCD_SetBackColor(LCD_BLACK & 0x80FFFFFF);  // 设置背景色透明度，高8位的数字越小透明度越高，ARGB4444支持4位透明色，有16种透明状态
	LCD_SetColor(LCD_WHITE);		 
	LCD_DisplayText(28,140,"STM32H750XBH6 LTDC, ARGB4444，layer1"); 
	HAL_Delay(1000);
		
	LCD_SetBackColor(LCD_BLACK & 0x30FFFFFF );  // 设置背景色透明度，高8位的数字越小透明度越高，ARGB4444支持4位透明色，有16种透明状态
	LCD_SetColor(LCD_WHITE);
	LCD_DisplayText(28,180,"STM32H750XBH6 LTDC, ARGB4444，layer1"); 	
	HAL_Delay(1000);
	
	LCD_SetBackColor(LCD_BLACK  );  				 // 将背景色设置为 不透明
	LCD_SetColor(LCD_WHITE & 0x00FFFFFF);		 // 将画笔色设置为 完全透明	 
	LCD_DisplayText(28,220,"STM32H750XBH6 LTDC, ARGB4444，layer1"); 	
	HAL_Delay(2000);	
	
#elif	ColorMode_1 == LTDC_PIXEL_FORMAT_ARGB1555	// 如果layer1 定义为 ARGB1555


	LCD_SetBackColor(LCD_BLACK & 0xffFFFFF);  // 设置背景色透明度，高8位的数字越小透明度越高，ARGB1555仅支持一位透明色，即仅有透明和不透明两种状态
	LCD_SetColor(LCD_WHITE);						// 画笔不透明 
	LCD_DisplayText(28,100,"STM32H750XBH6 LTDC, ARGB1555，layer1"); 
	HAL_Delay(1000);
	
	LCD_SetBackColor(LCD_BLACK & 0x00FFFFFF);  // 设置背景色透明度，高8位的数字越小透明度越高，ARGB1555仅支持一位透明色，即仅有透明和不透明两种状态
	LCD_SetColor(LCD_WHITE);						 // 画笔不透明 
	LCD_DisplayText(28,140,"STM32H750XBH6 LTDC, ARGB1555，layer1"); 
	HAL_Delay(1000);
		
	LCD_SetBackColor(LCD_BLACK  & 0xffFFFFF);  // 将背景色设置为 不透明
	LCD_SetColor(LCD_WHITE & 0x00FFFFFF);		 // 将画笔色设置为 完全透明	 
	LCD_DisplayText(28,180,"STM32H750XBH6 LTDC, ARGB1555，layer1"); 	
	HAL_Delay(2000);	
	
#endif


}

/*************************************************************************************************
*	函 数 名:	LCD_Test_Clear
*
*	函数功能:	清屏测试
*
*	说    明:	无	
*************************************************************************************************/

void LCD_Test_Clear(void)
{
	uint16_t time = 1000;	// 延时时间
	uint8_t	i = 0;			// 计数变量
	
// 绘制初始界面，包括标题、LOGO以及进度条>>>>>
	
	LCD_SetBackColor(0xffB9EDF8); 			//	设置背景色，使用自定义颜色
	LCD_Clear(); 									//	清屏，刷背景色
	
	LCD_SetTextFont(&CH_Font32);				// 设置3232中文字体,ASCII字体对应为3216
	LCD_SetColor(0xff333333);					//	设置画笔色，使用自定义颜色
	LCD_DisplayText(176, 87,"刷屏测试");	// 显示文本
	
	LCD_SetColor(0xfffd7923);					//	设置画笔色，使用自定义颜色
	LCD_DrawImage(  120, 120, 240, 83, Image_FANKE_240x83) ;		// 显示LOGO图片

	LCD_SetColor(0xff003366);					//	设置画笔色，使用自定义颜色	
	for(i=0;i<100;i++)
   {
		LCD_FillRect(44,228,4*i,6);	// 绘制矩形，实现简易进度条的效果
		HAL_Delay(15);	
   }	
	
	
	
// 刷屏测试>>>>>
		
	LCD_SetTextFont(&CH_Font24);			// 设置2424中文字体,ASCII字体对应为2412
	LCD_SetColor(LCD_BLACK);				// 设置画笔颜色

	for(i=0;i<8;i++)
	{
		switch (i)		// 切换背景色
		{
			case 0: LCD_SetBackColor(LIGHT_RED); 		break;	
			case 1: LCD_SetBackColor(LIGHT_GREEN); 	break;				
			case 2: LCD_SetBackColor(LIGHT_BLUE); 		break;
			case 3: LCD_SetBackColor(LIGHT_YELLOW); 	break;
			case 4: LCD_SetBackColor(LIGHT_CYAN);		break;
			case 5: LCD_SetBackColor(LIGHT_GREY); 		break;
			case 6: LCD_SetBackColor(LIGHT_MAGENTA); 	break;
			case 7: LCD_SetBackColor(LCD_WHITE); 		break;			
			default:	break;			
		}
		LCD_Clear();		// 清屏
		LCD_DisplayText(68, 68,"STM32H750 LTDC 刷屏测试");
		LCD_DisplayText(68,106,"核心板型号：FK750M4-XBH6");
		LCD_DisplayText(68,144,"屏幕分辨率：480*272");		
		HAL_Delay(time);	// 延时
	}
}

/*************************************************************************************************
*	函 数 名:	LCD_Test_Text
*
*	函数功能:	文本显示测试
*
*	说    明:	无	
*************************************************************************************************/

void LCD_Test_Text(void)
{
	uint16_t i;					// 计数变量

// 绘制初始界面，包括标题、LOGO以及进度条>>>>>
	
	LCD_SetBackColor(0xffB9EDF8); 			//	设置背景色，使用自定义颜色
	LCD_Clear(); 									//	清屏，刷背景色
	
	LCD_SetTextFont(&CH_Font32);				// 设置3232中文字体,ASCII字体对应为3216
	LCD_SetColor(0xff333333);					//	设置画笔色，使用自定义颜色
	LCD_DisplayText(176, 87,"文本显示");	// 显示文本
	
	LCD_SetColor(0xfffd7923);					//	设置画笔色，使用自定义颜色
	LCD_DrawImage(  120, 120, 240, 83, Image_FANKE_240x83) ;		// 显示LOGO图片

	LCD_SetColor(0xff003366);					//	设置画笔色，使用自定义颜色	
	for(i=0;i<100;i++)
   {
		LCD_FillRect(44,228,4*i,6);	// 绘制矩形，实现简易进度条的效果
		HAL_Delay(15);	
   }
	
// 显示文本，包括各种字体大小的中文和ASCII字符 >>>>>

	LCD_SetBackColor(LCD_BLACK); 			//	设置背景色
	LCD_Clear(); 								// 清屏
	
	LCD_SetColor(LCD_WHITE);	// 设置画笔，白色
	LCD_SetFont(&Font32); LCD_DisplayString(0, 0,"!#$%&'()*+,-.0123456789:;<=>?"); 						    	HAL_Delay(80);	// 使用3216字体		
	LCD_SetFont(&Font24); LCD_DisplayString(0,32,"!#$%&'()*+,-.0123456789:;<=>?@ABCDEFGH"); 				   HAL_Delay(80);	// 使用2412字体
	LCD_SetFont(&Font20); LCD_DisplayString(0,56,"!#$%&'()*+,-.0123456789:;<=>?@ABCDEFGHIJKLMNO");      	HAL_Delay(80);	// 使用2010字体
	LCD_SetFont(&Font16); LCD_DisplayString(0,76,"!#$%&'()*+,-.0123456789:;<=>?@ABCDEFGHIJKLMNOPQRST"); 	HAL_Delay(80);	// 使用1608字体
	LCD_SetFont(&Font12); LCD_DisplayString(0,92,"!#$%&'()*+,-.0123456789:;<=>?@ABCDEFGHIJKLMNOPQRST"); 	HAL_Delay(80);	// 使用1206字体
																																				
	LCD_SetColor(LCD_CYAN);                                                                               	
	LCD_SetFont(&Font12); LCD_DisplayString(0,104,"!#$%&'()*+,-.0123456789:;<=>?@ABCDEFGHIJKLMNOPQRST"); 	HAL_Delay(80);	// 使用1206字体
	LCD_SetFont(&Font16); LCD_DisplayString(0,116,"!#$%&'()*+,-.0123456789:;<=>?@ABCDEFGHIJKLMNOPQRST"); 	HAL_Delay(80);	// 使用1608字体
	LCD_SetFont(&Font20); LCD_DisplayString(0,132,"!#$%&'()*+,-.0123456789:;<=>?@ABCDEFGHIJKLMNO");		  	HAL_Delay(80);	// 使用2010字体	
	LCD_SetFont(&Font24); LCD_DisplayString(0,152,"!#$%&'()*+,-.0123456789:;<=>?@ABCDEFGH"); 				  	HAL_Delay(80);	// 使用2412字体	
	LCD_SetFont(&Font32); LCD_DisplayString(0,176,"!#$%&'()*+,-.0123456789:;<=>?"); 							  	HAL_Delay(80);	// 使用3216字体	

	LCD_SetTextFont(&CH_Font24);			// 设置2424中文字体,ASCII字体对应为2412
	LCD_SetColor(LCD_YELLOW);				// 设置画笔，黄色
	LCD_DisplayText(0, 210,"文本显示，可显示中文和ASCII字符集");
	LCD_DisplayText(0, 240,"用户可根据需求，对字库进行增添和删减");	
	HAL_Delay(2000);	// 延时等待
	
	LCD_SetBackColor(LCD_BLACK); 			//	设置背景色
	LCD_Clear(); 								// 清屏	
	
	LCD_SetTextFont(&CH_Font12);			// 设置1212中文字体,ASCII字体对应为1206
	LCD_SetColor(LCD_WHITE);				// 设置画笔,白色
	LCD_DisplayText(28, 20,"1212中文字体：反客科技");	
	
	LCD_SetTextFont(&CH_Font16);			// 设置1616中文字体,ASCII字体对应为1608
	LCD_SetColor(LIGHT_RED);				// 设置画笔，亮红色
	LCD_DisplayText(28, 48,"1616中文字体：反客科技");		
	
	LCD_SetTextFont(&CH_Font20);			// 设置2020中文字体,ASCII字体对应为2010
	LCD_SetColor(LIGHT_RED);				// 设置画笔，亮红色
	LCD_DisplayText(28, 82,"2020中文字体：反客科技");		

	LCD_SetTextFont(&CH_Font24);			// 设置2424中文字体,ASCII字体对应为2412
	LCD_SetColor(LIGHT_CYAN);				// 设置画笔，蓝绿色
	LCD_DisplayText(28, 121,"2424中文字体：反客科技");		

	LCD_SetTextFont(&CH_Font32);			// 设置3232中文字体,ASCII字体对应为3216
	LCD_SetColor(LIGHT_CYAN);				// 设置画笔，蓝绿色
	LCD_DisplayText(28, 160,"3232中文字体：反客科技");		

	LCD_SetTextFont(&CH_Font24);			// 设置2424中文字体,ASCII字体对应为2412
	LCD_SetColor(LIGHT_YELLOW);			// 设置画笔，亮黄色
	LCD_DisplayText(28, 217,"核心板型号：FK750M4-XBH6");		

	HAL_Delay(2000);	// 延时等待
}

/*************************************************************************************************
*	函 数 名:	LCD_Test_Variable
*
*	函数功能:	变量显示，包括整数和小数
*
*	说    明:	无	
*************************************************************************************************/

void LCD_Test_Variable (void)
{

	uint16_t i;					// 计数变量

	int32_t	a = 0;			// 定义整数变量，用于测试
	int32_t	b = 0;			// 定义整数变量，用于测试
	int32_t	c = 0;			// 定义整数变量，用于测试

	double p = 3.1415926;	// 定义浮点数变量，用于测试
	double f = -1234.1234;	// 定义浮点数变量，用于测试
	
// 绘制初始界面，包括标题、LOGO以及进度条>>>>>
	
	LCD_SetBackColor(0xffB9EDF8); 			//	设置背景色，使用自定义颜色
	LCD_Clear(); 									//	清屏，刷背景色
	
	LCD_SetTextFont(&CH_Font32);				// 设置3232中文字体,ASCII字体对应为3216
	LCD_SetColor(0xff333333);					//	设置画笔色，使用自定义颜色
	LCD_DisplayText(176, 87,"变量显示");	// 显示文本
	
	LCD_SetColor(0xfffd7923);					//	设置画笔色，使用自定义颜色
	LCD_DrawImage(  120, 120, 240, 83, Image_FANKE_240x83) ;		// 显示LOGO图片

	LCD_SetColor(0xff003366);					//	设置画笔色，使用自定义颜色	
	for(i=0;i<100;i++)
   {
		LCD_FillRect(44,228,4*i,6);	// 绘制矩形，实现简易进度条的效果
		HAL_Delay(15);	
   }
	
// 显示正整数、负整数、小数>>>>>	
	
	LCD_SetBackColor(LCD_BLACK); 			//	设置背景色
	LCD_Clear(); 								// 清屏
	
	LCD_SetTextFont(&CH_Font24);				// 设置2424中文字体,ASCII字体对应为2412
	LCD_SetColor(LCD_WHITE);					// 设置画笔,白色
	
	LCD_DisplayText(28, 20,"多余位填充空格");	// 显示文本	
	LCD_DisplayText(261,20,"多余位填充0");		// 显示文本		
	
	LCD_SetColor(LIGHT_CYAN);					// 设置画笔，蓝绿色
	LCD_DisplayText(28, 61,"正整数：");				
	LCD_DisplayText(28, 92,"正整数：");				
	LCD_DisplayText(28,123,"负整数：");					
				
	LCD_SetColor(LIGHT_YELLOW);				// 设置画笔，亮黄色		
	LCD_DisplayText(261, 61,"正整数：");	
	LCD_DisplayText(261, 94,"正整数：");	
	LCD_DisplayText(261,127,"负整数：");	
			
	LCD_SetColor(LIGHT_RED);					// 设置画笔	，亮红色		
	LCD_DisplayText(28, 171,"正小数：");	
	LCD_DisplayText(28, 202,"负小数：");			
			
	for(i=0;i<100;i++)
   {
		LCD_SetColor(LIGHT_CYAN);									// 设置画笔	，蓝绿色	
		LCD_ShowNumMode(Fill_Space);								// 多余位填充空格
		LCD_DisplayNumber( 120,  61, a+i*125, 8) ;			// 显示变量		
		LCD_DisplayNumber( 120,  92, b+i, 	  6) ;			// 显示变量			
		LCD_DisplayNumber( 120, 123, c-i,     6) ;			// 显示变量			
		
		LCD_SetColor(LIGHT_YELLOW);								// 设置画笔，亮黄色	
		LCD_ShowNumMode(Fill_Zero);								// 多余位填充0
		LCD_DisplayNumber( 353,  61, a+i*125, 8) ;			// 显示变量		
		LCD_DisplayNumber( 353,  92, b+i, 	  6) ;			// 显示变量			
		LCD_DisplayNumber( 353, 123, c-i,     6) ;			// 显示变量				
		
		LCD_SetColor(LIGHT_RED);						// 设置画笔，亮红色			
		LCD_ShowNumMode(Fill_Space);					// 多余位填充空格		
		LCD_DisplayDecimals( 120, 171, p+i*0.1,  6,3);	// 显示小数	
		LCD_DisplayDecimals( 120, 202, f+i*0.01, 11,4);	// 显示小数		
		
		HAL_Delay(40);				
   }
	
	HAL_Delay(2500);		
	
}



/*************************************************************************************************
*	函 数 名:	LCD_Test_FillRect
*
*	函数功能:	矩形填充测试
*
*	说    明:	无	
*************************************************************************************************/

void LCD_Test_FillRect(void)
{
	uint16_t i;					// 计数变量
	
// 绘制初始界面，包括标题、LOGO以及进度条>>>>>
	
	LCD_SetBackColor(0xffB9EDF8); 			//	设置背景色，使用自定义颜色
	LCD_Clear(); 									//	清屏，刷背景色
	
	LCD_SetTextFont(&CH_Font32);				// 设置3232中文字体,ASCII字体对应为3216
	LCD_SetColor(0xff333333);					//	设置画笔色，使用自定义颜色
	LCD_DisplayText(176, 87,"矩形填充");	// 显示文本
	
	LCD_SetColor(0xfffd7923);					//	设置画笔色，使用自定义颜色
	LCD_DrawImage(  120, 120, 240, 83, Image_FANKE_240x83) ;		// 显示LOGO图片

	LCD_SetColor(0xff003366);					//	设置画笔色，使用自定义颜色	
	for(i=0;i<100;i++)
   {
		LCD_FillRect(44,228,4*i,6);	// 绘制矩形，实现简易进度条的效果
		HAL_Delay(15);	
   }
	
// 矩形填充>>>>>	
	
	LCD_SetBackColor(LCD_BLACK); //设置背景色
	LCD_Clear(); //清屏，刷背景色

	LCD_SetFont(&Font16);
	LCD_SetColor(LCD_BLUE);	  	  LCD_FillRect(130,  3,320,16);	LCD_DisplayString(0,  3,"LCD_BLUE");		  
	LCD_SetColor(LCD_GREEN);  	  LCD_FillRect(130, 25,320,16);  LCD_DisplayString(0, 25,"LCD_GREEN");		  
	LCD_SetColor(LCD_RED);    	  LCD_FillRect(130, 47,320,16);  LCD_DisplayString(0, 47,"LCD_RED");			  
	LCD_SetColor(LCD_CYAN);   	  LCD_FillRect(130, 69,320,16);  LCD_DisplayString(0, 69,"LCD_CYAN");		  
	LCD_SetColor(LCD_MAGENTA);	  LCD_FillRect(130, 91,320,16);  LCD_DisplayString(0, 91,"LCD_MAGENTA");	  
	LCD_SetColor(LCD_YELLOW); 	  LCD_FillRect(130,113,320,16);  LCD_DisplayString(0,113,"LCD_YELLOW");		  
	LCD_SetColor(LCD_GREY);   	  LCD_FillRect(130,135,320,16);	LCD_DisplayString(0,135,"LCD_GREY");		  
																																				
	LCD_SetColor(LIGHT_BLUE);	  LCD_FillRect(130,157,320,16);  LCD_DisplayString(0,157,"LIGHT_BLUE");		  
	LCD_SetColor(LIGHT_GREEN);   LCD_FillRect(130,179,320,16);  LCD_DisplayString(0,179,"LIGHT_GREEN");	  
	LCD_SetColor(LIGHT_RED);     LCD_FillRect(130,201,320,16);  LCD_DisplayString(0,201,"LIGHT_RED");	     
	LCD_SetColor(LIGHT_CYAN);    LCD_FillRect(130,223,320,16);  LCD_DisplayString(0,223,"LIGHT_CYAN");	     
	LCD_SetColor(LIGHT_MAGENTA); LCD_FillRect(130,245,320,16);  LCD_DisplayString(0,245,"LIGHT_MAGENTA");	  

	HAL_Delay(3000);
}


/*************************************************************************************************
*	函 数 名:	LCD_Test_Color
*
*	函数功能:	颜色测试
*
*	说    明:	无	
*************************************************************************************************/

void LCD_Test_Color(void)
{
	uint16_t i;
	
// 绘制初始界面，包括标题、LOGO以及进度条>>>>>
	
	LCD_SetBackColor(0xffB9EDF8); 			//	设置背景色，使用自定义颜色
	LCD_Clear(); 									//	清屏，刷背景色
	
	LCD_SetTextFont(&CH_Font32);				// 设置3232中文字体,ASCII字体对应为3216
	LCD_SetColor(0xff333333);					//	设置画笔色，使用自定义颜色
	LCD_DisplayText(176, 87,"颜色测试");	// 显示文本
	
	LCD_SetColor(0xfffd7923);					//	设置画笔色，使用自定义颜色
	LCD_DrawImage(  120, 120, 240, 83, Image_FANKE_240x83) ;		// 显示LOGO图片

	LCD_SetColor(0xff003366);					//	设置画笔色，使用自定义颜色	
	for(i=0;i<100;i++)
   {
		LCD_FillRect(44,228,4*i,6);	// 绘制矩形，实现简易进度条的效果
		HAL_Delay(15);	
   }
	
// 颜色测试>>>>>
		
	LCD_SetBackColor(LCD_BLACK); //设置背景色
	LCD_Clear(); //清屏，刷背景色
	
	LCD_SetTextFont(&CH_Font24);			// 设置2424中文字体,ASCII字体对应为2412
	LCD_SetColor(LCD_WHITE);				// 设置画笔颜色
	
	LCD_DisplayText(21,14,"核心板型号：FK750M4-XBH6");
	LCD_DisplayText(21,54,"屏幕分辨率：480*272");		
	LCD_DisplayText(21,94,"RGB三基色色阶测试");	
	
	//使用画线函数绘制三基色色条
	for(i=0;i<240;i++)
	{
		LCD_SetColor( LCD_RED-(i<<16) );
		LCD_DrawLine(5+2*i,  140,5+2*i,  170);	
		LCD_DrawLine(5+2*i+1,140,5+2*i+1,170);	
	}
	for(i=0;i<240;i++)
	{
		LCD_SetColor( LCD_GREEN-(i<<8) );
		LCD_DrawLine(5+2*i,  180,5+2*i,  210);	
		LCD_DrawLine(5+2*i+1,180,5+2*i+1,210);
	}
	for(i=0;i<240;i++)
	{
		LCD_SetColor( LCD_BLUE-i );
		LCD_DrawLine(5+2*i,  220,5+2*i,  250);	
		LCD_DrawLine(5+2*i+1,220,5+2*i+1,250);
	}	
	HAL_Delay(3000);	
	
	
}

/*************************************************************************************************
*	函 数 名:	LCD_Test_GrahicTest
*
*	函数功能:	2D图形绘制
*
*	说    明:	无	
*************************************************************************************************/

void LCD_Test_GrahicTest(void)
{
	uint16_t time = 80;		// 延时时间
	uint16_t i;					// 计数变量
		
// 绘制初始界面，包括标题、LOGO以及进度条>>>>>
	
	LCD_SetBackColor(0xffB9EDF8); 			//	设置背景色，使用自定义颜色
	LCD_Clear(); 									//	清屏，刷背景色
	
	LCD_SetTextFont(&CH_Font32);				// 设置3232中文字体,ASCII字体对应为3216
	LCD_SetColor(0xff333333);					//	设置画笔色，使用自定义颜色
	LCD_DisplayText(176, 87,"绘图测试");	// 显示文本
	
	LCD_SetColor(0xfffd7923);					//	设置画笔色，使用自定义颜色
	LCD_DrawImage(  120, 120, 240, 83, Image_FANKE_240x83) ;		// 显示LOGO图片

	LCD_SetColor(0xff003366);					//	设置画笔色，使用自定义颜色	
	for(i=0;i<100;i++)
   {
		LCD_FillRect(44,228,4*i,6);	// 绘制矩形，实现简易进度条的效果
		HAL_Delay(15);	
   }
	
// 2D图形绘制>>>>>>>
	
	LCD_SetBackColor(LCD_BLACK); //设置背景色
	LCD_Clear(); //清屏，刷背景色	

	LCD_SetColor(LCD_RED);    LCD_FillCircle( 60,200,60);		//填充圆形
	LCD_SetColor(LCD_GREEN);  LCD_FillCircle(100,200,60); 	
	LCD_SetColor(LCD_BLUE);   LCD_FillCircle(140,200,60);  	

	LCD_SetColor(LIGHT_GREY);
	LCD_DrawLine(5,5,200,5);	HAL_Delay(time);	//画直线
	LCD_DrawLine(5,10,150,10);	HAL_Delay(time);
	LCD_DrawLine(5,15,100,15); HAL_Delay(time);
	LCD_DrawLine(5,20,50,20);	HAL_Delay(time);	

	LCD_SetColor(LIGHT_CYAN);
	LCD_DrawCircle(350,60,60);	HAL_Delay(time);	//绘制圆形
	LCD_DrawCircle(350,60,50);   HAL_Delay(time);
	LCD_DrawCircle(350,60,40);   HAL_Delay(time);
	LCD_DrawCircle(350,60,30);   HAL_Delay(time);

	LCD_SetColor(LCD_RED);	
	LCD_DrawRect( 5,30,200,80);  HAL_Delay(time);	//绘制矩形
	LCD_DrawRect(30,35,150,70); HAL_Delay(time);
	LCD_DrawRect(55,40,100,60);  HAL_Delay(time);
	LCD_DrawRect(80,45, 50,50);   HAL_Delay(time);

	LCD_SetColor(LIGHT_MAGENTA);	
	LCD_DrawEllipse(350,200,100,50); HAL_Delay(time);	//绘制椭圆
	LCD_DrawEllipse(350,200,80,40);  HAL_Delay(time);
	LCD_DrawEllipse(350,200,60,30);  HAL_Delay(time);
	LCD_DrawEllipse(350,200,40,20);  HAL_Delay(time);

	HAL_Delay(2000);	
}
/*************************************************************************************************
*	函 数 名:	LCD_Test_Image
*
*	函数功能:	图片显示测试
*
*	说    明:	无	
*************************************************************************************************/

void LCD_Test_Image(void)
{
	uint16_t i;					// 计数变量
		
// 绘制初始界面，包括标题、LOGO以及进度条>>>>>
	
	LCD_SetBackColor(0xffB9EDF8); 			//	设置背景色，使用自定义颜色
	LCD_Clear(); 									//	清屏，刷背景色
	
	LCD_SetTextFont(&CH_Font32);				// 设置3232中文字体,ASCII字体对应为3216
	LCD_SetColor(0xff333333);					//	设置画笔色，使用自定义颜色
	LCD_DisplayText(176, 87,"图片绘制");	// 显示文本
	
	LCD_SetColor(0xfffd7923);					//	设置画笔色，使用自定义颜色
	LCD_DrawImage(  120, 120, 240, 83, Image_FANKE_240x83) ;		// 显示LOGO图片

	LCD_SetColor(0xff003366);					//	设置画笔色，使用自定义颜色	
	for(i=0;i<100;i++)
   {
		LCD_FillRect(44,228,4*i,6);	// 绘制矩形，实现简易进度条的效果
		HAL_Delay(15);	
   }
	
// 图片绘制>>>>>>>	

	LCD_SetBackColor(LCD_BLACK); 			//	设置背景色
	LCD_Clear(); 								// 清屏
	
	LCD_SetColor( 0xFFFFAD60);
	LCD_DrawImage( 84, 49, 60, 60, Image_Android_60x60) ;
	
	LCD_SetColor( 0xFFFFB6B9);
	LCD_DrawImage( 210, 55, 60, 60, Image_Cloud_60x60) ;
	
	LCD_SetColor( 0xFF8AC6D1);
	LCD_DrawImage( 336, 55, 60, 60, Image_Folder_60x60) ;

	LCD_SetColor( 0xFFFFF5C3);
	LCD_DrawImage( 84,  162, 60, 60, Image_Message_60x60) ;
	
	LCD_SetColor( 0xFFA696C8);
	LCD_DrawImage( 210, 162, 60, 60, Image_Toys_60x60) ;
	
	LCD_SetColor( 0xFFE59572);
	LCD_DrawImage( 336, 162, 60, 60, Image_Video_60x60) ;	

	HAL_Delay(2000);
	
	LCD_SetBackColor(LCD_WHITE); 			//	设置背景色
	LCD_Clear(); 								// 清屏
	LCD_SetColor( LCD_BLACK);
	LCD_DrawImage( 0, 16, 480, 239, Image_FANKE_480x239) ;	
	HAL_Delay(2000);
	
}


/*************************************************************************************************
*	函 数 名:	LCD_Test_Vertical
*
*	函数功能:	竖屏测试
*
*	说    明:	无	
*************************************************************************************************/

void  LCD_Test_Vertical(void)
{
	uint16_t i;
	uint16_t time = 100;	
	
	LCD_DisplayDirection(Direction_V); // 切换到竖屏显示
	
// 绘制初始界面，包括标题、LOGO以及进度条>>>>>
	
	LCD_SetBackColor(0xffB9EDF8); 			//	设置背景色，使用自定义颜色
	LCD_Clear(); 									//	清屏，刷背景色
	
	LCD_SetTextFont(&CH_Font32);				// 设置3232中文字体,ASCII字体对应为3216
	LCD_SetColor(0xff333333);					//	设置画笔色，使用自定义颜色
	LCD_DisplayText(72, 100,"竖屏显示");	// 显示文本
	
	LCD_SetColor(0xfffd7923);					//	设置画笔色，使用自定义颜色
	LCD_DrawImage( 16, 150, 240, 83, Image_FANKE_240x83) ;		// 显示LOGO图片

	LCD_SetColor(0xff003366);					//	设置画笔色，使用自定义颜色	
	for(i=0;i<130;i++)
   {
		LCD_FillRect(6,250,2*i,6);	// 绘制矩形，实现简易进度条的效果
		HAL_Delay(10);	
   }
	
// 绘制其它内容>>>>>>>		
	
	LCD_SetBackColor(LCD_BLACK); //设置背景色
	LCD_Clear(); //清屏，刷背景色		

	LCD_SetColor(LCD_WHITE);
	LCD_SetFont(&Font32);LCD_DisplayString(0, 0,"!#$%&'()*+,-.012"); 					HAL_Delay(time);		
	LCD_SetFont(&Font24);LCD_DisplayString(0,32,"!#$%&'()*+,-.0123456");			 	HAL_Delay(time);
	LCD_SetFont(&Font20);LCD_DisplayString(0,56,"!#$%&'()*+,-.012345678"); 			HAL_Delay(time);	
	LCD_SetFont(&Font16);LCD_DisplayString(0,76,"!#$%&'()*+,-.0123456789:;"); 		HAL_Delay(time);	
	LCD_SetFont(&Font12);LCD_DisplayString(0,92,"!#$%&'()*+,-.0123456789:;<=>"); 	HAL_Delay(time);	
                                                                                                      
	LCD_SetColor(LCD_CYAN);                                                                            
	LCD_SetFont(&Font12);LCD_DisplayString(0,104,"!#$%&'()*+,-.0123456789:;<=>");	HAL_Delay(time);	
	LCD_SetFont(&Font16);LCD_DisplayString(0,116,"!#$%&'()*+,-.0123456789:;");		HAL_Delay(time);	
	LCD_SetFont(&Font20);LCD_DisplayString(0,132,"!#$%&'()*+,-.012345678");			HAL_Delay(time);		
	LCD_SetFont(&Font24);LCD_DisplayString(0,152,"!#$%&'()*+,-.0123456");			HAL_Delay(time);		
	LCD_SetFont(&Font32);LCD_DisplayString(0,176,"!#$%&'()*+,-.012");					HAL_Delay(time);	

	LCD_SetFont(&Font32);
	LCD_SetColor(LCD_YELLOW);
	LCD_DisplayNumber(10,220, 294967295,10); HAL_Delay(time);		
	LCD_DisplayNumber(10,260,123456,6);	      HAL_Delay(time);		
	LCD_DisplayNumber(10,300,1234,4);		   HAL_Delay(time);		
	LCD_DisplayNumber(10,340,0,0);			   HAL_Delay(time);		
	 
	LCD_SetFont(&Font24);
	LCD_SetColor(LIGHT_BLUE);
	LCD_DisplayString(10,380,"STM32H750 LCD TEST");HAL_Delay(time);

	HAL_Delay(2000);

	time = 80;
	
	LCD_SetBackColor(LCD_BLACK); //设置背景色
	LCD_Clear(); //清屏，刷背景色	
	
	LCD_SetColor(LCD_RED);    LCD_FillCircle( 90,240,80);	
	LCD_SetColor(LCD_GREEN);  LCD_FillCircle(135,240,80); 
	LCD_SetColor(LCD_BLUE);   LCD_FillCircle(180,240,80);  	
	
   LCD_SetColor(LCD_RED);	
	LCD_DrawRect( 0,35,270,100);  HAL_Delay(time);
	LCD_DrawRect(20,45,230,80); 	HAL_Delay(time);
	LCD_DrawRect(40,55,190,60);  	HAL_Delay(time);
	LCD_DrawRect(60,65,150,40);  	HAL_Delay(time);
	
	LCD_SetColor(LIGHT_GREY);
	LCD_DrawLine(0,5, 271,5);	HAL_Delay(time);
	LCD_DrawLine(0,10,271,10);	HAL_Delay(time);
	LCD_DrawLine(0,15,271,15); HAL_Delay(time);
	LCD_DrawLine(0,20,271,20);	HAL_Delay(time);		

   LCD_SetColor(LIGHT_MAGENTA);	
	LCD_DrawEllipse(135,400,130,70); HAL_Delay(time);
	LCD_DrawEllipse(135,400,110,55);  HAL_Delay(time);
	LCD_DrawEllipse(135,400,90 ,40);  HAL_Delay(time);
	LCD_DrawEllipse(135,400,70 ,25);  HAL_Delay(time);
                                                        
	HAL_Delay(2000);	
	
	LCD_SetBackColor(LCD_BLACK); //设置背景色
	LCD_Clear(); //清屏，刷背景色

	LCD_SetFont(&Font16);
	LCD_SetColor(LCD_BLUE);	  	  LCD_FillRect(120,  3,150,16);	LCD_DisplayString(0,  3,"LCD_BLUE"); 			
	LCD_SetColor(LCD_GREEN);  	  LCD_FillRect(120, 25,150,16);  LCD_DisplayString(0, 25,"LCD_GREEN");	
	LCD_SetColor(LCD_RED);    	  LCD_FillRect(120, 47,150,16);  LCD_DisplayString(0, 47,"LCD_RED");	 	
	LCD_SetColor(LCD_CYAN);   	  LCD_FillRect(120, 69,150,16);  LCD_DisplayString(0, 69,"LCD_CYAN");		
	LCD_SetColor(LCD_MAGENTA);	  LCD_FillRect(120, 91,150,16);  LCD_DisplayString(0, 91,"LCD_MAGENTA");	
	LCD_SetColor(LCD_YELLOW); 	  LCD_FillRect(120,113,150,16);  LCD_DisplayString(0,113,"LCD_YELLOW");		
	LCD_SetColor(LCD_GREY);   	  LCD_FillRect(120,135,150,16);	LCD_DisplayString(0,135,"LCD_GREY");		
                                                                            
	LCD_SetColor(LIGHT_BLUE);	  LCD_FillRect(120,157,150,16);  LCD_DisplayString(0,157,"LIGHT_BLUE");		
	LCD_SetColor(LIGHT_GREEN);   LCD_FillRect(120,179,150,16);  LCD_DisplayString(0,179,"LIGHT_GREEN");	
	LCD_SetColor(LIGHT_RED);     LCD_FillRect(120,201,150,16);  LCD_DisplayString(0,201,"LIGHT_RED");	   
	LCD_SetColor(LIGHT_CYAN);    LCD_FillRect(120,223,150,16);  LCD_DisplayString(0,223,"LIGHT_CYAN");	   
	LCD_SetColor(LIGHT_MAGENTA); LCD_FillRect(120,245,150,16);  LCD_DisplayString(0,245,"LIGHT_MAGENTA");	
	LCD_SetColor(LIGHT_YELLOW);  LCD_FillRect(120,267,150,16);  LCD_DisplayString(0,267,"LIGHT_YELLOW");	
	LCD_SetColor(LIGHT_GREY);    LCD_FillRect(120,289,150,16);	LCD_DisplayString(0,289,"LIGHT_GREY");  	
	                                                                             
	LCD_SetColor(DARK_BLUE);	  LCD_FillRect(120,311,150,16);  LCD_DisplayString(0,311,"DARK_BLUE");		
	LCD_SetColor(DARK_GREEN);    LCD_FillRect(120,333,150,16);  LCD_DisplayString(0,333,"DARK_GREEN");		
	LCD_SetColor(DARK_RED);      LCD_FillRect(120,355,150,16);  LCD_DisplayString(0,355,"DARK_RED");		
	LCD_SetColor(DARK_CYAN);     LCD_FillRect(120,377,150,16);  LCD_DisplayString(0,377,"DARK_CYAN");		
	LCD_SetColor(DARK_MAGENTA);  LCD_FillRect(120,399,150,16);  LCD_DisplayString(0,399,"DARK_MAGENTA");	
	LCD_SetColor(DARK_YELLOW);   LCD_FillRect(120,421,150,16);  LCD_DisplayString(0,421,"DARK_YELLOW");	
	LCD_SetColor(DARK_GREY);     LCD_FillRect(120,443,150,16);	LCD_DisplayString(0,443,"DARK_GREY");		
	
	HAL_Delay(2000);	
	
	LCD_SetBackColor(LCD_BLACK); //设置背景色
	LCD_Clear(); //清屏，刷背景色

	LCD_SetColor(LCD_RED);    	LCD_DisplayString(0,3,"0XFF0000");	
	LCD_SetColor(LCD_GREEN);  	LCD_DisplayString(0,25,"0X00FF00");
	LCD_SetColor(LCD_BLUE);	  	LCD_DisplayString(0,47,"0X0000FF");	
	
	//刷颜色条
	for(i=70;i<255;i++){LCD_SetColor( LCD_RED-(i<<16) ); 		LCD_DrawLine(80+i-70,  3,80+i-70, 19);}
	for(i=70;i<255;i++){LCD_SetColor( LCD_GREEN-(i<<8) );		LCD_DrawLine(80+i-70, 25,80+i-70, 41);}
	for(i=70;i<255;i++){LCD_SetColor( LCD_BLUE-i );		 		LCD_DrawLine(80+i-70, 47,80+i-70, 63);}
	for(i=70;i<255;i++){LCD_SetColor( LIGHT_RED-(i<<16) );	LCD_DrawLine(80+i-70, 69,80+i-70, 85);}LCD_DisplayString(0, 69,"0xFF8080");
	for(i=70;i<255;i++){LCD_SetColor( LIGHT_GREEN-(i<<8) );	LCD_DrawLine(80+i-70, 91,80+i-70,107);}LCD_DisplayString(0, 91,"0x80FF80");
	for(i=70;i<255;i++){LCD_SetColor( LIGHT_BLUE-i );			LCD_DrawLine(80+i-70,113,80+i-70,129);}LCD_DisplayString(0,113,"0x8080FF");	
	for(i=70;i<255;i++){LCD_SetColor( DARK_BLUE-(i<<16) );	LCD_DrawLine(80+i-70,135,80+i-70,151);}LCD_DisplayString(0,135,"0x000080");	
	for(i=70;i<255;i++){LCD_SetColor( DARK_BLUE-(i<<8) );		LCD_DrawLine(80+i-70,157,80+i-70,173);}LCD_DisplayString(0,157,"0x000080");	
	for(i=70;i<255;i++){LCD_SetColor( DARK_RED-i );				LCD_DrawLine(80+i-70,179,80+i-70,195);}LCD_DisplayString(0,179,"0x800000");		
	for(i=70;i<255;i++){LCD_SetColor( DARK_RED-(i<<8));		LCD_DrawLine(80+i-70,201,80+i-70,217);}LCD_DisplayString(0,201,"0x800000");	
	for(i=70;i<255;i++){LCD_SetColor( DARK_GREEN-(i<<16)); 	LCD_DrawLine(80+i-70,223,80+i-70,239);}LCD_DisplayString(0,223,"0x008000");	
	for(i=70;i<255;i++){LCD_SetColor( DARK_GREEN-i);			LCD_DrawLine(80+i-70,245,80+i-70,261);}LCD_DisplayString(0,245,"0x008000");	
	for(i=70;i<255;i++){LCD_SetColor( DARK_CYAN-(i<<16));		LCD_DrawLine(80+i-70,267,80+i-70,283);}LCD_DisplayString(0,267,"0x008080");	
	for(i=70;i<255;i++){LCD_SetColor( DARK_YELLOW-i);			LCD_DrawLine(80+i-70,289,80+i-70,305);}LCD_DisplayString(0,289,"0x808000");	
	for(i=70;i<255;i++){LCD_SetColor( DARK_MAGENTA-(i<<8));	LCD_DrawLine(80+i-70,311,80+i-70,327);}LCD_DisplayString(0,311,"0x800080");	
                                                                                          
	HAL_Delay(2000);	
	LCD_DisplayDirection(Direction_H); // 切换回横屏显示
	
}







