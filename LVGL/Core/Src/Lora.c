#include "Lora.h"
#include "stm32h7xx_hal.h"
#include "usart.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FreeRTOS.h"
#include "queue.h"

uint8_t LoRa_buf[256];
uint8_t LoRa_cnt = 0;					//接收计数器
uint8_t LoRa_cntPre = 0;			//最终接收计数器
uint8_t UART3_RX_Buf;					//单字节接收缓冲区

			
extern QueueHandle_t xDeviceDataQueue;		//获取到的设备数据


void LoRa_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	
	__HAL_RCC_GPIOE_CLK_ENABLE();
	
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_9,GPIO_PIN_RESET);			//默认关闭
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_11,GPIO_PIN_RESET);			//默认关闭
	
	GPIO_InitStruct.Pin = GPIO_PIN_9 | GPIO_PIN_11;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;							
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	
	HAL_GPIO_Init(GPIOE,&GPIO_InitStruct);
	
	//调整LoRa模块至透传模式			M1M0==00
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_9,GPIO_PIN_RESET);			
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_11,GPIO_PIN_RESET);			

}

void LoRa_Clear(void)
{
	memset(LoRa_buf,0,sizeof(LoRa_buf));
	LoRa_cnt = 0;
}

//等待接收完成
_Bool LoRa_WaitRecive(void)
{

	if(LoRa_cnt == 0) 							//如果接收计数为0 则说明没有处于接收数据中，所以直接跳出，结束函数
		return REV_WAIT;												//未接收到数据，返回0
	if(LoRa_cnt == LoRa_cntPre)	//如果上一次的值和这次相同，则说明接收完毕
	{
		LoRa_cnt = 0;								//清空接收计数
		printf("LoRa模块接收到的数据：%s\r\n",LoRa_buf);
		return REV_OK;												//接收到数据，返回1
	}
	LoRa_cntPre = LoRa_cnt;			//置为相同
	
	return REV_WAIT;													//未接收完数据，返回0

}

//从字符串提取键值对
static float parse_float(const char *str) {
    return (str != NULL) ? atof(str) : 0.0f;
}

static int parse_int(const char *str) {
    return (str != NULL) ? atoi(str) : 0;
}



void LoRa_GetDataPack(uint8_t Device_id)
{
		//判断数据包是不是我给的样子，是就要不是就丢了
		char *data = (char *)LoRa_buf; 
	
		SubData device_data;
     
    char id_str[16];
    snprintf(id_str, sizeof(id_str), "id:%d", Device_id);
    if (strstr(data, id_str) == NULL) {
        printf("警告:ID不匹配 (预期:%d)\r\n", Device_id);
        return;
    }

    char *saveptr;
    char *token = strtok_r(data, ",", &saveptr);
    int valid_fields = 0;

    while (token != NULL) {
        char *key = strtok(token, ":");
        char *value = strtok(NULL, ":");

        if (key && value) {
            if (strcmp(key, "gps_n") == 0) {
                device_data.gps_n = parse_float(value);
                valid_fields++;
            } else if (strcmp(key, "gps_e") == 0) {
                device_data.gps_e = parse_float(value);
                valid_fields++;
            } else if (strcmp(key, "ntu") == 0) {
                device_data.ntu = parse_float(value);
                valid_fields++;
            } else if (strcmp(key, "tds") == 0) {
                device_data.tds = parse_int(value);
                valid_fields++;
            } else if (strcmp(key, "temp") == 0) {
                device_data.temp = parse_float(value);
                valid_fields++;
            } else if (strcmp(key, "battery") == 0) {
                device_data.battery = parse_int(value);
                valid_fields++;
            } else if (strcmp(key, "ph") == 0) {
                device_data.ph = parse_float(value);
                valid_fields++;
            }
        }
        token = strtok_r(NULL, ",", &saveptr);
    }
 
    if (valid_fields < 5) {
        printf("警告：数据包字段不完整 (%d/7)\r\n", valid_fields);
        memset(&device_data, 0, sizeof(SubData)); 
    } else {
        printf("成功解析 %d 数据包\r\n", Device_id);
				xQueueOverwrite(xDeviceDataQueue, &device_data);		//覆盖获取到的数据
        HAL_UART_Transmit(&huart3,(unsigned char *)"OK\r\n",sizeof("OK\r\n"),100);
    }
}

extern char lora[16];

//发送的间隔最好弄大点
void LoRa_Try2GetData(uint8_t Device)
{
    char ASK[8];
    for(uint8_t i=1; i<=Device; i++)
    {
        unsigned char timeout = 50;  //等待重发时间2s
        uint8_t retry_count = 3;
        _Bool received = 0;  

        
        LoRa_Clear();

        while(retry_count--)
        {
            sprintf(ASK, "id:%d", i);
            Usart_SendString(&huart3, (unsigned char*)ASK, strlen(ASK));

            // 超时循环等待
            for(uint8_t time=0; time<timeout; time++)
            {
                if(LoRa_WaitRecive() == REV_OK)
                {
                    printf("成功接收到设备 %d 的信息\r\n", i);
                    received = 1; 
										//解析数据
										LoRa_GetDataPack(i);	//解析第i个数据
										snprintf(lora,sizeof(lora),"LoRa: Connect");
									
									
                    break;          
                }
                vTaskDelay(40);
            }

            if(received) break;     // 收到了
        }

        if(!received)
        {
						snprintf(lora,sizeof(lora),"LoRa: Disable");
						printf("未收到设备%d响应\r\n", i);
        }
				
				
    }
		return;	//回家吧孩子
}

