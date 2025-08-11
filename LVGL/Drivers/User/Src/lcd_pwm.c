/***
>>>>> �ļ�˵����
	*
	*  1.PWMƵ��Ϊ 20 KHz
	*	2.HAL_TIM_MspPostInit���ڳ�ʼ��IO�ڣ�HAL_TIM_Base_MspInit���ڿ���ʱ��
	*
	************************************************************************************************
***/


#include "lcd_pwm.h"

TIM_HandleTypeDef htim8;	// TIM_HandleTypeDef �ṹ�����

static uint16_t LCD_PwmPeriod = 500;  		//��ʱ������ֵ

/*************************************************************************************************
*	�� �� ��:	HAL_TIM_MspPostInit
*	��ڲ���:	htim - TIM_HandleTypeDef�ṹ�����������ʾ�����TIM�������
*	�� �� ֵ:	��
*	��������:	��ʼ�� TIM ��Ӧ��PWM��
*	˵    ��:	��ʼ��PWM�õ�������
*
*************************************************************************************************/

void HAL_TIM_MspPostInit(TIM_HandleTypeDef* htim)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	if(htim->Instance == LTDC_PWM_TIM)
	{
		GPIO_LDC_Backlight_CLK_ENABLE;			// �����������Ŷ˿�ʱ��

		GPIO_InitStruct.Pin 			= LTDC_PWM_PIN;			// ��������
		GPIO_InitStruct.Mode 		= GPIO_MODE_AF_PP;		// �����������
		GPIO_InitStruct.Pull 		= GPIO_NOPULL;				// ��������
		GPIO_InitStruct.Speed		= GPIO_SPEED_FREQ_LOW;	// ����ģʽ
		GPIO_InitStruct.Alternate 	= LCD_PWM_AF;				// ����
		
		HAL_GPIO_Init(LTDC_PWM_PORT, &GPIO_InitStruct);		// ��ʼ��IO��
	}
}  


/*************************************************************************************************
*	�� �� ��:	LCD_PwmSetPulse
*	��ڲ���:	pulse - PWMռ�ձȣ���Χ 0~100
*	�� �� ֵ:	��
*	��������:	����PWMռ�ձ�
*	˵    ��:	��
*************************************************************************************************/
	
void  LCD_PwmSetPulse (uint8_t pulse)
{
	uint16_t compareValue ; 
	
	compareValue = pulse * LCD_PwmPeriod / 100; //����ռ�ձ����ñȽ�ֵ

	TIM8->CCR4 = compareValue; 			// �޸�TIM8��ͨ��4�Ƚ�ֵ
}

/*************************************************************************************************
*	�� �� ��:	LCD_PWMinit
*	��ڲ���:	pulse - PWMռ�ձȣ���Χ 0~100
*	�� �� ֵ:	��
*	��������:	��ʼ��TIM,����PWMƵ��Ϊ2 KHz
*	˵    ��:	��
*************************************************************************************************/

void  LCD_PWMinit(uint8_t pulse)
{

	TIM_ClockConfigTypeDef sClockSourceConfig = {0};
	TIM_MasterConfigTypeDef sMasterConfig = {0};
	TIM_OC_InitTypeDef sConfigOC = {0};

	htim8.Instance 					= LTDC_PWM_TIM;							// ��ʱ��
	htim8.Init.Prescaler 			= 23;                              // Ԥ��Ƶϵ������ʱ��ʱ���ļ���Ƶ��Ϊ 10 MHz
	htim8.Init.CounterMode 			= TIM_COUNTERMODE_UP;               // ���ϼ���ģʽ
	htim8.Init.Period 				= LCD_PwmPeriod -1 ;                // ����ֵ499��������500��
	htim8.Init.ClockDivision 		= TIM_CLOCKDIVISION_DIV1;           // ʱ�Ӳ���Ƶ
	htim8.Init.AutoReloadPreload 	= TIM_AUTORELOAD_PRELOAD_DISABLE;   // ���ƼĴ��� TIMx_CR1 ��ARPE λ��0������ֹ�Զ����ؼĴ�������Ԥװ��

	HAL_TIM_Base_Init(&htim8) ;	// ��������Ĳ�������TIM���г�ʼ��

	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;			// ѡ���ڲ�ʱ��Դ
	HAL_TIM_ConfigClockSource(&htim8, &sClockSourceConfig);           // ��ʼ������ʱ��Դ

	HAL_TIM_PWM_Init(&htim8) ;		// ��������Ĳ�������TIM����PWM��ʼ��   

	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;					// �������ѡ�񣬴�ʱ���ø�λģʽ�����Ĵ��� TIMx_CR2 �� MMS ΪΪ000
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;      // ��ʹ�ô�ģʽ
	HAL_TIMEx_MasterConfigSynchronization(&htim8, &sMasterConfig);    // ��ʼ������

	sConfigOC.OCMode		= TIM_OCMODE_PWM1;											// PWMģʽ1
	sConfigOC.Pulse 		= pulse*LCD_PwmPeriod/100;									// �Ƚ�ֵ250������Ϊ500����ռ�ձ�Ϊ50%
	sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;										// ��Ч״̬Ϊ�ߵ�ƽ
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;										// ��ֹ����ģʽ
	HAL_TIM_PWM_ConfigChannel(&htim8, &sConfigOC, LTDC_PWM_TIM_CHANNEL);		// ��ʼ������PWM

	HAL_TIM_MspPostInit(&htim8);								// ��ʼ��IO��
	HAL_TIM_PWM_Start(&htim8,LTDC_PWM_TIM_CHANNEL);		// ����PWM			
}

/*************************************************************************************************
*	�� �� ��:	HAL_TIM_Base_MspInit
*	��ڲ���:	htim_base - TIM_HandleTypeDef�ṹ�����������ʾ�����TIM�������
*	�� �� ֵ:	��
*	��������:	����ʱ��
*	˵    ��:	��
*
*************************************************************************************************/

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* htim_base)
{
  if(htim_base->Instance==LTDC_PWM_TIM)
  {
    LTDC_PWM_TIM_CLK_ENABLE;		// ���� TIM ʱ��
  }

}

/*************************************************************************************************
*	�� �� ��:	LCD_PwmGetPulse
*	��ڲ���:	��
*	�� �� ֵ:	uint8_t - ��ǰռ�ձ�0-100%
*	��������:	��ȡ��ǰPWMռ�ձ�
*	˵    ��:	����TIM8ͨ��4��CCR�Ĵ���ֵ��Ԥ�������ڼ���
*************************************************************************************************/
uint8_t LCD_PwmGetPulse(void)
{
    
    uint16_t current_ccr = TIM8->CCR4;
    
    //����ʵ��ռ�ձ�
    return (uint8_t)((current_ccr * 100) / LCD_PwmPeriod);
}

