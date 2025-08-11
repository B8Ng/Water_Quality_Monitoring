#include "main.h"
#include "led.h"
#include "usart.h"
#include "lcd_rgb.h"
#include "lcd_pwm.h"
#include "touch_480x272.h"
#include "FreeRTOS.h"
#include "task.h"
#include "lvgl.h"
#include "lv_port_disp_template.h"
#include "lv_port_indev_template.h"
#include "usart.h"
#include "gui_guider.h"
#include "events_init.h"

#include <stdio.h>
#include "DX511.h"
#include "Lora.h"

#include "queue.h"
#include "semphr.h"

lv_ui guider_ui;
SubData device_data;

extern uint8_t UART3_RX_Buf;					//���ֽڽ��ջ�����

//dclock��ʱ��ȫ�ֱ���
extern int MainUI_digital_clock_1_hour_value;
extern int MainUI_digital_clock_1_min_value;
extern int MainUI_digital_clock_1_sec_value;
extern SensorSettingData SettingData;


TaskHandle_t NetWork_taskhandle;
TaskHandle_t ReciveOneNetData_taskhandle;
TaskHandle_t LVGL_taskhandle;
TaskHandle_t LED_taskhandle;
TaskHandle_t Ping_taskhandle;


/*								LVGLȫ�ֱ���							*/

char node_num[13]="Node Num: 0";	//���255���ӽڵ�

char dimness[12]="NTU:0.0";				//NodeUI��DetailUI��Ҫ����ˢ��
char temp[8]="T: 0";
char tds[9]="TDS: 0";
char ph[9]="PH: 0.0";
char gps[20]="GPS: NO SIGNAL";

char lora[16] = "LoRa: Connect";
char warning[12]= "Warning:0";		//MainUI  NodeUI DetailUI ����ˢ�µ���Ҫ

char warning_log[1024];						//����buff

uint8_t Warning_cnt = 0;	//���������



/*								LVGLȫ�ֱ���							*/

QueueHandle_t xDeviceDataQueue;
QueueHandle_t xSettingDataQueue;
QueueHandle_t xTimeUpdateQueue;
QueueHandle_t xDeviceNumberQueue;



void Judge2GenerateWarnings(SensorSettingData SettingData,SubData device_data)
{
		char warning_msg[256];
		int has_warning = 0;		//��־λ
		snprintf(warning_msg,sizeof(warning_msg),"time:%d:%d:%d\n",MainUI_digital_clock_1_hour_value,MainUI_digital_clock_1_min_value,MainUI_digital_clock_1_sec_value);
		if(device_data.ntu>SettingData.NTU_H)
		{
			char temp[32];
			printf("NTU����,%0.1f>%d\r\n",device_data.ntu,SettingData.NTU_H);
			snprintf(temp,sizeof(temp),"NTU is too high (%0.1f > %d)\n", device_data.ntu, SettingData.NTU_H);
			strncat(warning_msg, temp, sizeof(warning_msg) - strlen(warning_msg) - 1);
			has_warning = 1;
		}
		if(device_data.ph > SettingData.PH_H)
		{
			char temp[32];
			printf("PH����\r\n");
			snprintf(temp,sizeof(temp),"PH is too high (%0.1f > %d)\n", device_data.ph, SettingData.PH_H);
			strncat(warning_msg, temp, sizeof(warning_msg) - strlen(warning_msg) - 1);
			has_warning = 1;
		}
		else if(device_data.ph < SettingData.PH_L)
		{
			char temp[32];
			printf("PH����\r\n");
			snprintf(temp,sizeof(temp),"PH is too low (%0.1f < %d)\n", device_data.ph, SettingData.PH_L);
			strncat(warning_msg, temp, sizeof(warning_msg) - strlen(warning_msg) - 1);
			has_warning = 1;
		}
		
		if(device_data.tds>SettingData.TDS_H)
		{		
			char temp[32];
			printf("tds����\r\n");
			snprintf(temp,sizeof(temp),"TDS is too high (%d > %d)\n", device_data.tds, SettingData.TDS_H);
			strncat(warning_msg, temp, sizeof(warning_msg) - strlen(warning_msg) - 1);
			has_warning = 1;
		}
		
		if(device_data.temp>SettingData.Temperature_H)
		{
			char temp[32];
			printf("ˮ�¹���\r\n");
			snprintf(temp,sizeof(temp),"Temp is too high (%0.1f > %d)\n", device_data.temp, SettingData.Temperature_H);
			strncat(warning_msg, temp, sizeof(warning_msg) - strlen(warning_msg) - 1);
			has_warning = 1;
		}
		else if(device_data.temp < SettingData.Temperature_L)
		{
			char temp[32];
			printf("ˮ�¹���\r\n");
			snprintf(temp,sizeof(temp),"Temp is too low (%0.1f < %d)\n", device_data.temp, SettingData.Temperature_L);
			strncat(warning_msg, temp, sizeof(warning_msg) - strlen(warning_msg) - 1);
			has_warning = 1;
		}
		if(has_warning)//����о���ľͼ�һ
		{
			printf("%s", warning_msg);
			Warning_cnt++;	//���������+1
			snprintf(warning,sizeof(warning),"Warning:%d",Warning_cnt);
			
			//д��ȥ���buff����
			size_t remaining_space = sizeof(warning_log) - strlen(warning_log) - 1;
      size_t total_length = strlen(warning_msg) + strlen(warning_msg);

			if (total_length <= remaining_space)
			{
					strncat(warning_log, warning_msg, remaining_space);
			}
			else
			{
					// ���˾��ȵ�������һ��
					memset(warning_log,0,sizeof(warning_log));
					strncat(warning_log, warning_msg, remaining_space);
					printf("Warning log buffer is full.\n");
			}
		}
		
}


void FreeRTOS_Init(void)
{
	xDeviceDataQueue = xQueueCreate(1, sizeof(SubData));
	xSettingDataQueue = xQueueCreate(1, sizeof(SensorSettingData));
	xTimeUpdateQueue = xQueueCreate(1, sizeof(RealTime));
	xDeviceNumberQueue = xQueueCreate(1, sizeof(uint8_t));
}




//���շ����������������ø�������
static void ReciveOneNetData_task(void *arg)
{

	while(1)
	{
		DX511_GetData(5);		//ֱ�Ӹ�ȫ�ֺ���SensorSettingData SettingData
		
		vTaskDelay(1);
	}
}

//30s pingһ��
static void NetWork_Ping_task(void *arg)
{
	while(1)
	{
		//printf("������Ц��֮������\r\n");
		DX511_Ping();
		vTaskDelay(30000);			
	}
}

static void LED_task(void *arg)
{
	while(1)
	{
		LED1_Toggle;			// LEDָʾ
		vTaskDelay(100);
		
	}
}


static void LVGL_task(void *arg)
{
	setup_ui(&guider_ui);
	events_init(&guider_ui);
	
	RealTime currentTime;
	uint8_t DeviceNumber;
	
	while(1)
	{
		lv_task_handler();	// LVGL����
		Touch_Scan();			// ����
		
		//��ȡ��������ʾʱ�����Ϣ����
		if(xQueueReceive(xTimeUpdateQueue, &currentTime, 0)== pdPASS)
		{
			//printf("%2d:%2d:%2d\r\n",currentTime.hour,currentTime.minute,currentTime.second);
			//���µ�lvgl����
			MainUI_digital_clock_1_hour_value = currentTime.hour;
			MainUI_digital_clock_1_min_value = currentTime.minute;
			MainUI_digital_clock_1_sec_value = currentTime.second;
		
		}
		
		//�����ӽڵ�����
		if(xQueuePeek(xDeviceNumberQueue, &DeviceNumber, 0) == pdPASS)
		{
			//printf("��ǰ���ӽڵ�������:%d\r\n",DeviceNumber);
			
			snprintf(node_num,sizeof(node_num),"Node Num: %d",DeviceNumber);
		}

		
		
		
		vTaskDelay(15);
	}
}

static void NetWork_task(void *arg)
{
	uint8_t DeviceNumber = 0;
	
	
	DX511_Init();
	DX511_ON();
	LoRa_Init();
	HAL_UART_Receive_IT(&huart3,(uint8_t *)&UART3_RX_Buf, 1);
	//printf("��������\r\n");
	DX511_NetWork_Config();
	DX511_NetWork_Connect();
	DX511_NetWork_Sub_Number();
	DX511_NetWork_Sub_Connect();
	
	DX511_Publish_GateWay_Setting(SettingData.NTU_H,SettingData.PH_H,SettingData.PH_L,SettingData.TDS_H,SettingData.Temperature_H,SettingData.Temperature_L);
	DX511_GetTimeUpdate();	
	//taskENTER_CRITICAL(); 
	xTaskCreate(ReciveOneNetData_task,"ReciveOneNetData",512,NULL,6,&ReciveOneNetData_taskhandle);		//	����һ�����շ������������õ�����
	xTaskCreate(NetWork_Ping_task,"NetWork_Ping",128,NULL,3,&Ping_taskhandle);					//	����һ�����ڼ���Ƿ�����������ߵ�����
	//taskEXIT_CRITICAL(); 
	while(1)
	{
		if(xQueuePeek(xDeviceNumberQueue, &DeviceNumber, 0)== pdPASS)
		{
			printf("��ȡ�����豸�����ǣ�%d\r\n",DeviceNumber);
			LoRa_Try2GetData(DeviceNumber);
			if((xQueueReceive(xDeviceDataQueue, &device_data, 0) == pdPASS))
			{
				if(device_data.gps_n||device_data.gps_e||device_data.ntu||device_data.tds||device_data.temp||device_data.battery||device_data.ph != 0)
				{
						//���������ȸ��°�
						snprintf(dimness,sizeof(dimness),"NTU:%d",(int)(device_data.ntu));
						snprintf(temp,sizeof(temp),"T:%0.1f",device_data.temp);
						snprintf(tds,sizeof(tds),"TDS:%d",device_data.tds);
						snprintf(ph,sizeof(ph),"PH:%0.1f",device_data.ph);
						if(device_data.gps_e!=0 && device_data.gps_n !=0)
						{
							snprintf(gps,sizeof(gps),"GPS:%0.2fN %0.2fE",device_data.gps_n,device_data.gps_e);
						}
						else
						{
							snprintf(gps,sizeof(gps),"GPS: NO SIGNAL");
							
						}
						Judge2GenerateWarnings(SettingData,device_data);
						
					
						//���Ϸ�����
						DX511_Publish_Sub_Data(device_data.gps_n,device_data.gps_e,device_data.ntu,device_data.tds,device_data.temp,device_data.battery,device_data.ph);
					
					
						//���µ�lvgl����NodeUI��DetailUI
//						snprintf(dimness,sizeof(dimness),"NTU:%0.1f",device_data.ntu);
//						snprintf(temp,sizeof(temp),"T:%0.1f",device_data.temp);
//						snprintf(tds,sizeof(tds),"TDS:%d",device_data.tds);
//						snprintf(ph,sizeof(ph),"PH:%0.1f",device_data.ph);
						if(device_data.gps_e!=0 && device_data.gps_n !=0)
						{
							snprintf(gps,sizeof(gps),"GPS:%0.2fN %0.2fE",device_data.gps_n,device_data.gps_e);
						}
						else		//��������0˵��û�ź�
						{
							snprintf(gps,sizeof(gps),"GPS: NO SIGNAL");
							
						}


						
						
				}
			}
			
		}
		//
		//DX511_Publish_GateWay_Setting_New(SettingData.NTU_H,SettingData.PH_H,SettingData.PH_L,SettingData.TDS_H,SettingData.Temperature_H,SettingData.Temperature_L);
		//DX511_Publish_GateWay_Setting(SettingData.NTU_H,SettingData.PH_H,SettingData.PH_L,SettingData.TDS_H,SettingData.Temperature_H,SettingData.Temperature_L);
		vTaskDelay(3000);
		//vTaskDelay(1000);
	}

}




/********************************************** �������� *******************************************/

void SystemClock_Config(void);		// ʱ�ӳ�ʼ��
void MPU_Config(void);					// MPU����


int main(void)
{	
	MPU_Config();	
	SCB_EnableICache();		// ʹ��ICache
	SCB_EnableDCache();		// ʹ��DCache
	HAL_Init();					// ��ʼ��HAL��	
	SystemClock_Config();	// ����ϵͳʱ�ӣ���Ƶ480MHz
	LED_Init();					// ��ʼ��LED����

	MX_USART1_UART_Init();				// USART1��ʼ��	
	MX_USART2_UART_Init();
	MX_USART3_UART_Init();

	MX_LTDC_Init();			// LTDC�Լ����ʼ�� 
	LCD_PWMinit(40);			// ��������PWM��ʼ����ռ�ձ�40%
	Touch_Init();				// ��������ʼ��		
	printf("���س�ʼ��\r\n");
	lv_init();					//	LVGL��ʼ��
	lv_port_disp_init();		//LVGL��ʾ�ӿڳ�ʼ��
	lv_port_indev_init();	// LVGL�����ӿڳ�ʼ��				 

	FreeRTOS_Init();
	xTaskCreate(LED_task,"led",128, NULL, 2,&LED_taskhandle);
	xTaskCreate(LVGL_task,"lvgl",4096, NULL, 9,&LVGL_taskhandle);
	xTaskCreate(NetWork_task,"network",2048, NULL, 7,&NetWork_taskhandle);
	vTaskStartScheduler();
	
	
	
	printf("�Ѿ�������\r\n");

	while (1);

}

/****************************************************************************************************/
/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow : 
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 480000000 (CPU Clock)
  *            HCLK(Hz)                       = 240000000 (AXI and AHBs Clock)
  *            AHB Prescaler                  = 2
  *            D1 APB3 Prescaler              = 2 (APB3 Clock  120MHz)
  *            D2 APB1 Prescaler              = 2 (APB1 Clock  120MHz)
  *            D2 APB2 Prescaler              = 2 (APB2 Clock  120MHz)
  *            D3 APB4 Prescaler              = 2 (APB4 Clock  120MHz)
  *            HSE Frequency(Hz)              = 25000000
  *            PLL_M                          = 5
  *            PLL_N                          = 192
  *            PLL_P                          = 2
  *            PLL_Q                          = 2
  *            PLL_R                          = 2
  *            VDD(V)                         = 3.3
  *            Flash Latency(WS)              = 4
  * @param  None
  * @retval None
  */
/****************************************************************************************************/  
/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Supply configuration update enable
  */
  HAL_PWREx_ConfigSupply(PWR_LDO_SUPPLY);
  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE0);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}
  /** Macro to configure the PLL clock source
  */
  __HAL_RCC_PLL_PLLSOURCE_CONFIG(RCC_PLLSOURCE_HSE);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 5;
  RCC_OscInitStruct.PLL.PLLN = 192;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_2;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_D3PCLK1|RCC_CLOCKTYPE_D1PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
  

  /* ����LTDCʱ�ӣ���������Ϊ10MHz����ˢ������60֡���ң����߻��߹��Ͷ��������˸ */
  /* LCD clock configuration */
  /* PLL3_VCO Input = HSE_VALUE/PLL3M = 1 Mhz */
  /* PLL3_VCO Output = PLL3_VCO Input * PLL3N = 200 Mhz */
  /* PLLLCDCLK = PLL3_VCO Output/PLL3R = 200/20 = 10 Mhz */
  /* LTDC clock frequency = PLLLCDCLK = 10 Mhz */  
  
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_LTDC|RCC_PERIPHCLK_USART1;
  PeriphClkInitStruct.PLL3.PLL3M = 25;
  PeriphClkInitStruct.PLL3.PLL3N = 200;
  PeriphClkInitStruct.PLL3.PLL3P = 2;
  PeriphClkInitStruct.PLL3.PLL3Q = 2;
  PeriphClkInitStruct.PLL3.PLL3R = 20;
  PeriphClkInitStruct.PLL3.PLL3RGE = RCC_PLL3VCIRANGE_0;
  PeriphClkInitStruct.PLL3.PLL3VCOSEL = RCC_PLL3VCOMEDIUM;
  PeriphClkInitStruct.PLL3.PLL3FRACN = 0;
  PeriphClkInitStruct.Usart16ClockSelection = RCC_USART16CLKSOURCE_D2PCLK2;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
}

//	MPU����
//
void MPU_Config(void)
{
	MPU_Region_InitTypeDef MPU_InitStruct;

	HAL_MPU_Disable(); // ����֮ǰ�Ƚ�ֹMPU

	MPU_InitStruct.Enable 				= MPU_REGION_ENABLE;
	MPU_InitStruct.BaseAddress 		= LCD_MemoryAdd;
	MPU_InitStruct.Size 					= MPU_REGION_SIZE_512KB;
	MPU_InitStruct.AccessPermission 	= MPU_REGION_FULL_ACCESS;
	MPU_InitStruct.IsBufferable 		= MPU_ACCESS_NOT_BUFFERABLE;
	MPU_InitStruct.IsCacheable 		= MPU_ACCESS_NOT_CACHEABLE;
	MPU_InitStruct.IsShareable 		= MPU_ACCESS_NOT_SHAREABLE;
	MPU_InitStruct.Number 				= MPU_REGION_NUMBER0;
	MPU_InitStruct.TypeExtField 		= MPU_TEX_LEVEL0;
	MPU_InitStruct.SubRegionDisable 	= 0x00;
	MPU_InitStruct.DisableExec 		= MPU_INSTRUCTION_ACCESS_ENABLE;

	HAL_MPU_ConfigRegion(&MPU_InitStruct);


	HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);	// ʹ��MCU
}


//HAL��ʱ��Դ
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{

  if (htim->Instance == TIM6)
  {
    HAL_IncTick();
  }

}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
