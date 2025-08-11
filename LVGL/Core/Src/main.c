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

extern uint8_t UART3_RX_Buf;					//单字节接收缓冲区

//dclock定时器全局变量
extern int MainUI_digital_clock_1_hour_value;
extern int MainUI_digital_clock_1_min_value;
extern int MainUI_digital_clock_1_sec_value;
extern SensorSettingData SettingData;


TaskHandle_t NetWork_taskhandle;
TaskHandle_t ReciveOneNetData_taskhandle;
TaskHandle_t LVGL_taskhandle;
TaskHandle_t LED_taskhandle;
TaskHandle_t Ping_taskhandle;


/*								LVGL全局变量							*/

char node_num[13]="Node Num: 0";	//最多255个子节点

char dimness[12]="NTU:0.0";				//NodeUI和DetailUI需要用来刷新
char temp[8]="T: 0";
char tds[9]="TDS: 0";
char ph[9]="PH: 0.0";
char gps[20]="GPS: NO SIGNAL";

char lora[16] = "LoRa: Connect";
char warning[12]= "Warning:0";		//MainUI  NodeUI DetailUI 都有刷新的需要

char warning_log[1024];						//警告buff

uint8_t Warning_cnt = 0;	//警告计数器



/*								LVGL全局变量							*/

QueueHandle_t xDeviceDataQueue;
QueueHandle_t xSettingDataQueue;
QueueHandle_t xTimeUpdateQueue;
QueueHandle_t xDeviceNumberQueue;



void Judge2GenerateWarnings(SensorSettingData SettingData,SubData device_data)
{
		char warning_msg[256];
		int has_warning = 0;		//标志位
		snprintf(warning_msg,sizeof(warning_msg),"time:%d:%d:%d\n",MainUI_digital_clock_1_hour_value,MainUI_digital_clock_1_min_value,MainUI_digital_clock_1_sec_value);
		if(device_data.ntu>SettingData.NTU_H)
		{
			char temp[32];
			printf("NTU过高,%0.1f>%d\r\n",device_data.ntu,SettingData.NTU_H);
			snprintf(temp,sizeof(temp),"NTU is too high (%0.1f > %d)\n", device_data.ntu, SettingData.NTU_H);
			strncat(warning_msg, temp, sizeof(warning_msg) - strlen(warning_msg) - 1);
			has_warning = 1;
		}
		if(device_data.ph > SettingData.PH_H)
		{
			char temp[32];
			printf("PH过高\r\n");
			snprintf(temp,sizeof(temp),"PH is too high (%0.1f > %d)\n", device_data.ph, SettingData.PH_H);
			strncat(warning_msg, temp, sizeof(warning_msg) - strlen(warning_msg) - 1);
			has_warning = 1;
		}
		else if(device_data.ph < SettingData.PH_L)
		{
			char temp[32];
			printf("PH过低\r\n");
			snprintf(temp,sizeof(temp),"PH is too low (%0.1f < %d)\n", device_data.ph, SettingData.PH_L);
			strncat(warning_msg, temp, sizeof(warning_msg) - strlen(warning_msg) - 1);
			has_warning = 1;
		}
		
		if(device_data.tds>SettingData.TDS_H)
		{		
			char temp[32];
			printf("tds过高\r\n");
			snprintf(temp,sizeof(temp),"TDS is too high (%d > %d)\n", device_data.tds, SettingData.TDS_H);
			strncat(warning_msg, temp, sizeof(warning_msg) - strlen(warning_msg) - 1);
			has_warning = 1;
		}
		
		if(device_data.temp>SettingData.Temperature_H)
		{
			char temp[32];
			printf("水温过高\r\n");
			snprintf(temp,sizeof(temp),"Temp is too high (%0.1f > %d)\n", device_data.temp, SettingData.Temperature_H);
			strncat(warning_msg, temp, sizeof(warning_msg) - strlen(warning_msg) - 1);
			has_warning = 1;
		}
		else if(device_data.temp < SettingData.Temperature_L)
		{
			char temp[32];
			printf("水温过低\r\n");
			snprintf(temp,sizeof(temp),"Temp is too low (%0.1f < %d)\n", device_data.temp, SettingData.Temperature_L);
			strncat(warning_msg, temp, sizeof(warning_msg) - strlen(warning_msg) - 1);
			has_warning = 1;
		}
		if(has_warning)//如果有警告的就加一
		{
			printf("%s", warning_msg);
			Warning_cnt++;	//警告计数器+1
			snprintf(warning,sizeof(warning),"Warning:%d",Warning_cnt);
			
			//写进去大的buff里面
			size_t remaining_space = sizeof(warning_log) - strlen(warning_log) - 1;
      size_t total_length = strlen(warning_msg) + strlen(warning_msg);

			if (total_length <= remaining_space)
			{
					strncat(warning_log, warning_msg, remaining_space);
			}
			else
			{
					// 满了就先倒了再来一次
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




//接收服务器返回来的设置更新数据
static void ReciveOneNetData_task(void *arg)
{

	while(1)
	{
		DX511_GetData(5);		//直接给全局函数SensorSettingData SettingData
		
		vTaskDelay(1);
	}
}

//30s ping一次
static void NetWork_Ping_task(void *arg)
{
	while(1)
	{
		//printf("哈吉板笑传之连连线\r\n");
		DX511_Ping();
		vTaskDelay(30000);			
	}
}

static void LED_task(void *arg)
{
	while(1)
	{
		LED1_Toggle;			// LED指示
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
		lv_task_handler();	// LVGL进程
		Touch_Scan();			// 触摸
		
		//获取到更新显示时间的消息队列
		if(xQueueReceive(xTimeUpdateQueue, &currentTime, 0)== pdPASS)
		{
			//printf("%2d:%2d:%2d\r\n",currentTime.hour,currentTime.minute,currentTime.second);
			//更新到lvgl里面
			MainUI_digital_clock_1_hour_value = currentTime.hour;
			MainUI_digital_clock_1_min_value = currentTime.minute;
			MainUI_digital_clock_1_sec_value = currentTime.second;
		
		}
		
		//更新子节点数量
		if(xQueuePeek(xDeviceNumberQueue, &DeviceNumber, 0) == pdPASS)
		{
			//printf("当前的子节点数量是:%d\r\n",DeviceNumber);
			
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
	//printf("我在这里\r\n");
	DX511_NetWork_Config();
	DX511_NetWork_Connect();
	DX511_NetWork_Sub_Number();
	DX511_NetWork_Sub_Connect();
	
	DX511_Publish_GateWay_Setting(SettingData.NTU_H,SettingData.PH_H,SettingData.PH_L,SettingData.TDS_H,SettingData.Temperature_H,SettingData.Temperature_L);
	DX511_GetTimeUpdate();	
	//taskENTER_CRITICAL(); 
	xTaskCreate(ReciveOneNetData_task,"ReciveOneNetData",512,NULL,6,&ReciveOneNetData_taskhandle);		//	创建一个接收服务器更新设置的任务
	xTaskCreate(NetWork_Ping_task,"NetWork_Ping",128,NULL,3,&Ping_taskhandle);					//	创建一个定期检查是否跟服务器连线的任务
	//taskEXIT_CRITICAL(); 
	while(1)
	{
		if(xQueuePeek(xDeviceNumberQueue, &DeviceNumber, 0)== pdPASS)
		{
			printf("获取到的设备数量是：%d\r\n",DeviceNumber);
			LoRa_Try2GetData(DeviceNumber);
			if((xQueueReceive(xDeviceDataQueue, &device_data, 0) == pdPASS))
			{
				if(device_data.gps_n||device_data.gps_e||device_data.ntu||device_data.tds||device_data.temp||device_data.battery||device_data.ph != 0)
				{
						//事已至此先更新吧
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
						
					
						//发上服务器
						DX511_Publish_Sub_Data(device_data.gps_n,device_data.gps_e,device_data.ntu,device_data.tds,device_data.temp,device_data.battery,device_data.ph);
					
					
						//更新到lvgl界面NodeUI和DetailUI
//						snprintf(dimness,sizeof(dimness),"NTU:%0.1f",device_data.ntu);
//						snprintf(temp,sizeof(temp),"T:%0.1f",device_data.temp);
//						snprintf(tds,sizeof(tds),"TDS:%d",device_data.tds);
//						snprintf(ph,sizeof(ph),"PH:%0.1f",device_data.ph);
						if(device_data.gps_e!=0 && device_data.gps_n !=0)
						{
							snprintf(gps,sizeof(gps),"GPS:%0.2fN %0.2fE",device_data.gps_n,device_data.gps_e);
						}
						else		//两个都是0说明没信号
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




/********************************************** 函数声明 *******************************************/

void SystemClock_Config(void);		// 时钟初始化
void MPU_Config(void);					// MPU配置


int main(void)
{	
	MPU_Config();	
	SCB_EnableICache();		// 使能ICache
	SCB_EnableDCache();		// 使能DCache
	HAL_Init();					// 初始化HAL库	
	SystemClock_Config();	// 配置系统时钟，主频480MHz
	LED_Init();					// 初始化LED引脚

	MX_USART1_UART_Init();				// USART1初始化	
	MX_USART2_UART_Init();
	MX_USART3_UART_Init();

	MX_LTDC_Init();			// LTDC以及层初始化 
	LCD_PWMinit(40);			// 背光引脚PWM初始化，占空比40%
	Touch_Init();				// 触摸屏初始化		
	printf("网关初始化\r\n");
	lv_init();					//	LVGL初始化
	lv_port_disp_init();		//LVGL显示接口初始化
	lv_port_indev_init();	// LVGL触摸接口初始化				 

	FreeRTOS_Init();
	xTaskCreate(LED_task,"led",128, NULL, 2,&LED_taskhandle);
	xTaskCreate(LVGL_task,"lvgl",4096, NULL, 9,&LVGL_taskhandle);
	xTaskCreate(NetWork_task,"network",2048, NULL, 7,&NetWork_taskhandle);
	vTaskStartScheduler();
	
	
	
	printf("已经结束力\r\n");

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
  

  /* 设置LTDC时钟，这里设置为10MHz，即刷新率在60帧左右，过高或者过低都会造成闪烁 */
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

//	MPU配置
//
void MPU_Config(void)
{
	MPU_Region_InitTypeDef MPU_InitStruct;

	HAL_MPU_Disable(); // 设置之前先禁止MPU

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


	HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);	// 使能MCU
}


//HAL库时基源
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
