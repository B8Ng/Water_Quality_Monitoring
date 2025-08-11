#include "Lora.h"
#include "stm32h7xx_hal.h"
#include "usart.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FreeRTOS.h"
#include "queue.h"

uint8_t LoRa_buf[256];
uint8_t LoRa_cnt = 0;					//���ռ�����
uint8_t LoRa_cntPre = 0;			//���ս��ռ�����
uint8_t UART3_RX_Buf;					//���ֽڽ��ջ�����

			
extern QueueHandle_t xDeviceDataQueue;		//��ȡ�����豸����


void LoRa_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	
	__HAL_RCC_GPIOE_CLK_ENABLE();
	
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_9,GPIO_PIN_RESET);			//Ĭ�Ϲر�
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_11,GPIO_PIN_RESET);			//Ĭ�Ϲر�
	
	GPIO_InitStruct.Pin = GPIO_PIN_9 | GPIO_PIN_11;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;							
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	
	HAL_GPIO_Init(GPIOE,&GPIO_InitStruct);
	
	//����LoRaģ����͸��ģʽ			M1M0==00
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_9,GPIO_PIN_RESET);			
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_11,GPIO_PIN_RESET);			

}

void LoRa_Clear(void)
{
	memset(LoRa_buf,0,sizeof(LoRa_buf));
	LoRa_cnt = 0;
}

//�ȴ��������
_Bool LoRa_WaitRecive(void)
{

	if(LoRa_cnt == 0) 							//������ռ���Ϊ0 ��˵��û�д��ڽ��������У�����ֱ����������������
		return REV_WAIT;												//δ���յ����ݣ�����0
	if(LoRa_cnt == LoRa_cntPre)	//�����һ�ε�ֵ�������ͬ����˵���������
	{
		LoRa_cnt = 0;								//��ս��ռ���
		printf("LoRaģ����յ������ݣ�%s\r\n",LoRa_buf);
		return REV_OK;												//���յ����ݣ�����1
	}
	LoRa_cntPre = LoRa_cnt;			//��Ϊ��ͬ
	
	return REV_WAIT;													//δ���������ݣ�����0

}

//���ַ�����ȡ��ֵ��
static float parse_float(const char *str) {
    return (str != NULL) ? atof(str) : 0.0f;
}

static int parse_int(const char *str) {
    return (str != NULL) ? atoi(str) : 0;
}



void LoRa_GetDataPack(uint8_t Device_id)
{
		//�ж����ݰ��ǲ����Ҹ������ӣ��Ǿ�Ҫ���ǾͶ���
		char *data = (char *)LoRa_buf; 
	
		SubData device_data;
     
    char id_str[16];
    snprintf(id_str, sizeof(id_str), "id:%d", Device_id);
    if (strstr(data, id_str) == NULL) {
        printf("����:ID��ƥ�� (Ԥ��:%d)\r\n", Device_id);
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
        printf("���棺���ݰ��ֶβ����� (%d/7)\r\n", valid_fields);
        memset(&device_data, 0, sizeof(SubData)); 
    } else {
        printf("�ɹ����� %d ���ݰ�\r\n", Device_id);
				xQueueOverwrite(xDeviceDataQueue, &device_data);		//���ǻ�ȡ��������
        HAL_UART_Transmit(&huart3,(unsigned char *)"OK\r\n",sizeof("OK\r\n"),100);
    }
}

extern char lora[16];

//���͵ļ�����Ū���
void LoRa_Try2GetData(uint8_t Device)
{
    char ASK[8];
    for(uint8_t i=1; i<=Device; i++)
    {
        unsigned char timeout = 50;  //�ȴ��ط�ʱ��2s
        uint8_t retry_count = 3;
        _Bool received = 0;  

        
        LoRa_Clear();

        while(retry_count--)
        {
            sprintf(ASK, "id:%d", i);
            Usart_SendString(&huart3, (unsigned char*)ASK, strlen(ASK));

            // ��ʱѭ���ȴ�
            for(uint8_t time=0; time<timeout; time++)
            {
                if(LoRa_WaitRecive() == REV_OK)
                {
                    printf("�ɹ����յ��豸 %d ����Ϣ\r\n", i);
                    received = 1; 
										//��������
										LoRa_GetDataPack(i);	//������i������
										snprintf(lora,sizeof(lora),"LoRa: Connect");
									
									
                    break;          
                }
                vTaskDelay(40);
            }

            if(received) break;     // �յ���
        }

        if(!received)
        {
						snprintf(lora,sizeof(lora),"LoRa: Disable");
						printf("δ�յ��豸%d��Ӧ\r\n", i);
        }
				
				
    }
		return;	//�ؼҰɺ���
}

