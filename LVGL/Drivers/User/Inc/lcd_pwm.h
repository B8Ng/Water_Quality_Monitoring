#ifndef __PWM_H
#define __PWM_H 
 
 
#include "stm32h7xx_hal.h"
#include "lcd_rgb.h" 
 
#define  LTDC_PWM_PIN								GPIO_PIN_2								// ����			
#define	LTDC_PWM_PORT								GPIOI										// �˿�
#define 	GPIO_LTDC_PWM_CLK_ENABLE        	   __HAL_RCC_GPIOI_CLK_ENABLE()	 	// ʱ��
#define  LCD_PWM_AF           					GPIO_AF3_TIM8							// ����
	
#define  LTDC_PWM_TIM								TIM8										// ��ʱ��
#define  LTDC_PWM_TIM_CLK_ENABLE					__HAL_RCC_TIM8_CLK_ENABLE()		// ʱ��
#define  LTDC_PWM_TIM_CHANNEL					 	TIM_CHANNEL_4							// ͨ��


/*-------------------- �������� ----------------------*/

void LCD_PWMinit(uint8_t pulse);			 //PWM��ʼ��
void LCD_PwmSetPulse (uint8_t pulse);	 //����ռ�ձ�
uint8_t LCD_PwmGetPulse(void);

#endif //__PWM_H



