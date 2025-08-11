#include "DX511.h"
#include "usart.h"
#include "stm32h7xx_hal.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "Lora.h"

#include "FreeRTOS.h"
#include "queue.h"
#include "semphr.h"

/*                 DX511ģ��               */
uint8_t DX511_buf[256];				//���ջ�����
uint8_t DX511_cnt = 0;				//���ռ�����
uint8_t DX511_cntPre = 0;			//���ս��ռ�����
uint8_t UART_RX_Buf;					//���ֽڽ��ջ�����

extern int MainUI_digital_clock_1_hour_value;
extern int MainUI_digital_clock_1_min_value;
extern int MainUI_digital_clock_1_sec_value;

/*                 LoRaģ��            	   */
extern uint8_t LoRa_buf[256];
extern uint8_t LoRa_cnt;					//���ռ�����
extern uint8_t LoRa_cntPre;			//���ս��ռ�����
extern uint8_t UART3_RX_Buf;					//���ֽڽ��ջ�����


extern QueueHandle_t xSettingDataQueue;
extern QueueHandle_t xDeviceDataQueue;
extern QueueHandle_t xTimeUpdateQueue;
extern QueueHandle_t xDeviceNumberQueue;

SensorSettingData SettingData = {5,10.0,3.0,1000,30.0,0.0};

char node_connect[13] ="NetWork:NC" ;


//��ʼ��PG9���š���ʹ��4Gģ��EN��
void DX511_Init()
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	
	__HAL_RCC_GPIOG_CLK_ENABLE();
	
	HAL_GPIO_WritePin(GPIOG,GPIO_PIN_9,GPIO_PIN_RESET);			//Ĭ�Ϲر�
	
	GPIO_InitStruct.Pin = GPIO_PIN_9;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;							
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	
	HAL_GPIO_Init(GPIOG,&GPIO_InitStruct);
	
}


//����4Gģ�飬�����жϽ���
void DX511_ON(void)
{
	HAL_GPIO_WritePin(GPIOG,GPIO_PIN_9,GPIO_PIN_SET);
	HAL_UART_Receive_IT(&huart2,(uint8_t *)&UART_RX_Buf, 1);//���������ж�
}

//�ر�4Gģ��
void DX511_OFF(void)
{
	HAL_GPIO_WritePin(GPIOG,GPIO_PIN_9,GPIO_PIN_RESET);
}



//��ս��ջ�����
void DX511_Clear(void)
{
	memset(DX511_buf,0,sizeof(DX511_buf));
	DX511_cnt = 0;
}


//�ȴ��������
_Bool DX511_WaitRecive(void)
{

	if(DX511_cnt == 0) 							//������ռ���Ϊ0 ��˵��û�д��ڽ��������У�����ֱ����������������
		return REV_WAIT;												//δ���յ����ݣ�����0
	if(DX511_cnt == DX511_cntPre)	//�����һ�ε�ֵ�������ͬ����˵���������
	{
		DX511_cnt = 0;								//��ս��ռ���
		printf("4Gģ����յ������ݣ�%s\r\n",DX511_buf);
		return REV_OK;												//���յ����ݣ�����1
	}
	DX511_cntPre = DX511_cnt;			//��Ϊ��ͬ
	
	return REV_WAIT;													//δ���������ݣ�����0

}




//��������ȴ����عؼ���
_Bool DX511_SendCmd(char *cmd, char *res)
{
	
	unsigned char timeOut = 200;						//����ʱ��200
	Usart_SendString(&huart2, (unsigned char *)cmd, strlen((const char *)cmd));	//����ָ��
	while(timeOut--)
	{
		if(DX511_WaitRecive() == REV_OK)					//����յ�����
		{
			if(strstr((const char *)DX511_buf, res) != NULL)		//����������ؼ���
			{
				DX511_Clear();									//���DX511_buf����
				return 0;													//����0
			}
		}
		
		//vTaskDelay(10);
		HAL_Delay(10);
	}
	return 1;																//������ϣ�����1

}

uint8_t MAX_wait = 10;

//��������OneNET��Ҫ�Ĳ���	����֮ǰ��ʹ��EN��
void DX511_NetWork_Config(void)
{

	printf("RST\r\n");
	while(DX511_SendCmd("AT+RESET\r\n", "OK"))			vTaskDelay(500);
	vTaskDelay(4000);//�ȴ�4Gģ��������
	printf("AT����\r\n");
	while(DX511_SendCmd("AT\r\n", "OK"))	vTaskDelay(500);
	
	printf("����APN\r\n");
	while(DX511_SendCmd("AT+QICSGP=1,1,\"\",\"\",\"\"\r\n","OK"))	vTaskDelay(500);
	
	printf("����MQTT�ͻ��˷�����\r\n");
	while(DX511_SendCmd("AT+MCONFIG=\"H750\",\"87D45T0g17\",\"version=2018-10-31&res=products%2F87D45T0g17%2Fdevices%2FH750&et=1956499200&method=sha1&sign=Ssu4j7bK8smiWCcU%2FPEUevQPKkk%3D\"\r\n","OK")) vTaskDelay(500);
	
	printf("����MQTT������\r\n");
	while(DX511_SendCmd("AT+MIPSTART=\"87D45T0g17.mqtts.acc.cmcconenet.cn\",1883,4\r\n","OK"))	vTaskDelay(500);
	
	printf("��������������\r\n");
	return;
	

	
}



//���ӷ�����
void DX511_NetWork_Connect(void)
{
	printf("���ӷ�����\r\n");
	while(DX511_SendCmd("AT+MCONNECT=1,60\r\n","SUCCESS"))	vTaskDelay(500);
	printf("����������Ϣ\r\n");
	while(DX511_SendCmd("AT+MSUB=\"$sys/87D45T0g17/H750/thing/property/post/reply\",0\r\n","SUCCESS"))	vTaskDelay(500);
	printf("����������ģ����Ϣ\r\n");
	while(DX511_SendCmd("AT+MSUB=\"$sys/87D45T0g17/H750/thing/property/set\",0\r\n","SUCCESS"))	vTaskDelay(500);
	
	snprintf(node_connect,sizeof(node_connect),"NetWork:LTE");
}



//���� �ȶϿ�������������ʧ��4Gģ��
void DX511_NetWork_Disconnect(void)
{
	while(DX511_SendCmd("AT+MDISCONNECT\r\n","SUCCESS")) vTaskDelay(500);
	printf("�»�\r\n");
	DX511_OFF();
}





//��������Ϣ
void DX511_Publish(char *topic, char *Json, char *res)
{
	DX511_Clear();
	uint16_t data_len = strlen(Json);				//��ȡJson���ĳ���
	printf("Json���ĳ����ǣ�%d\r\n",data_len);
	char at_commad[256];
	snprintf(at_commad,sizeof(at_commad),"AT+MPUBEX=\"%s\",0,0,%d\r\n", topic, data_len);//ƴ��֡
	printf("%s\r\n",at_commad);
	if(DX511_SendCmd(at_commad,">")==0)
	{
		DX511_Clear();
		DX511_SendCmd(Json,res);
		printf("���ݰ��������\r\n");
	}
	else
	{
		printf("���ݸ���ʧ��\r\n");
	}

}



//���õ�ʱ����
//ƴ����������֡����
/*
NTU_H						1-5
PH_H						0-14
PH_L						0-14
TDS_H						0-1000
Temperature_H		-55-125
Temperature_L		-55-125

�������ʲ���Ҫ̫�죬ƽ̨���Ҳ��4s����һ��
*/
//����������
//�������
//ֱ����
void DX511_Publish_GateWay_Setting(int NTU_H,int PH_H,int PH_L,int TDS_H,int Temperature_H,int Temperature_L)
{
	char Json[256];
	 sprintf(Json,
        "{\"id\":\"666\",\"params\":{\"NTU_H\":{\"value\":%d},\"PH_H\":{\"value\":%d},\"PH_L\":{\"value\":%d},\"TDS_H\":{\"value\":%d},\"Temperature_H\":{\"value\":%d},\"Temperature_L\":{\"value\":%d}}}\r\n",
        NTU_H, PH_H, PH_L, TDS_H, Temperature_H, Temperature_L
    );

	DX511_Publish("$sys/87D45T0g17/H750/thing/property/post", Json, "OK");
	
}
//�ϰ�
//void DX511_Publish_GateWay_Setting_New(int NTU_H,float PH_H,float PH_L,int TDS_H,float Temperature_H,float Temperature_L)
//{
//	char Json[256];
//  sprintf(Json,
//        "AT+MPUB=\"$sys/87D45T0g17/H750/thing/property/post\",0,0,"
//        "\"{\"id\":\"123\","
//        "\"params\":{"
//            "\"PH_L\":{\"value\":%.2f},"
//            "\"PH_H\":{\"value\":%.2f},"
//            "\"NTU_H\":{\"value\":%d},"
//            "\"TDS_H\":{\"value\":%d},"
//            "\"Temperature_H\":{\"value\":%.2f},"
//            "\"Temperature_L\":{\"value\":%.2f}"
//        "}}\"", 
//        PH_L, PH_H, NTU_H, TDS_H, Temperature_H, Temperature_L);
//	DX511_SendCmd(Json,"SUCCESS");
//	printf("������\r\n");
//}



//��ȡ���豸��Ŀ
uint8_t DX511_Get_Sub_Num(char *topic, char *Json)
{
	DX511_Clear();
	uint16_t data_len = strlen(Json);				//��ȡJson���ĳ���
	printf("Json���ĳ����ǣ�%d\r\n",data_len);
	char at_commad[256];
	snprintf(at_commad,sizeof(at_commad),"AT+MPUBEX=\"%s\",0,0,%d\r\n", topic, data_len);//ƴ��֡
	printf("%s\r\n",at_commad);
	if(DX511_SendCmd(at_commad,">")==0)
	{
		DX511_Clear();
		
		//DX511_SendCmd(Json,res);
		unsigned char timeOut = 200;						//����ʱ��200
		Usart_SendString(&huart2, (unsigned char *)Json, strlen((const char *)Json));	//����ָ��
		while(timeOut--)
		{
			if (DX511_WaitRecive() == REV_OK) {
                char *reply_ptr = strstr((const char *)DX511_buf, "+MSUB:");
                if (reply_ptr != NULL) {
                   
                    char *json_start = strchr(reply_ptr, '{');
                    char *json_end = strrchr(reply_ptr, '}');
                    if (json_start && json_end) {
                        
                        size_t json_len = json_end - json_start + 1;
                        char json_copy[json_len + 1];
                        memcpy(json_copy, json_start, json_len);
                        json_copy[json_len] = '\0';

                        uint8_t count = 0;
                        char *device_ptr = json_copy;
                        while ((device_ptr = strstr(device_ptr, "\"deviceName\":")) != NULL) {
                            count++;
                            device_ptr += strlen("\"deviceName\":");
                        }
												
                        return count; 
                    }
                }
							}
		vTaskDelay(10);
		}
		
	}
	else
	{
		printf("���ݸ���ʧ��\r\n");
		
	}
	return 0;
}

//��ȡ���豸��Ŀ
void DX511_NetWork_Sub_Number(void)
{
	while(DX511_SendCmd("AT+MSUB=\"$sys/87D45T0g17/H750/thing/sub/topo/get/reply\",0\r\n","SUCCESS"))//������Ϣ
		vTaskDelay(100);
	printf("���豸���˶��ĳɹ�\r\n");
	//��ȡ���豸��Ŀ
	
	uint8_t deviceNumber = DX511_Get_Sub_Num("$sys/87D45T0g17/H750/thing/sub/topo/get", "{\"id\":\"123\",\"version\":\"1.0\"}");
	xQueueOverwrite(xDeviceNumberQueue, &deviceNumber);
	printf("deviceNumber = %d\r\n",deviceNumber);
	
}
//�ڵ��¼	��Loraͨ�����豸��Ŀ����
//͵����	Ӧ�ø�������Ľڵ���Կ�Լ���Ʒ�ϴ����ݵ�
void DX511_NetWork_Sub_Connect(void)
{
	DX511_Publish("$sys/87D45T0g17/H750/thing/sub/login","{\"id\":\"123\",\"version\":\"1.0\",\"params\":{\"deviceName\":\"Node0\",\"productID\":\"9YyMBQhEkr\",\"sasToken\":\"version=2018-10-31&res=products%2F9YyMBQhEkr%2Fdevices%2FNode0&et=1956499200&method=sha1&sign=ZN5Ha2RRZWU06jg1R7UwaPOMihI%3D\"}}\r\n","SUCCESS");
	printf("Node0�ڵ����߳ɹ�\r\n");
}
void DX511_NetWork_Sub_Disconnect(void)
{
	DX511_Publish("$sys/87D45T0g17/H750/thing/sub/logout","{\"id\":\"123\",\"version\":\"1.0\",\"params\":{\"deviceName\":\"Node0\",\"productID\":\"9YyMBQhEkr\",\"sasToken\":\"version=2018-10-31&res=products%2F9YyMBQhEkr%2Fdevices%2FNode0&et=1956499200&method=sha1&sign=ZN5Ha2RRZWU06jg1R7UwaPOMihI%3D\"}}\r\n","SUCCESS");
	printf("Node0�ڵ�������\r\n");
}

/*
gps_n						-90-90
gps_e						-180-180
tds							0-1000
temp						-40-55
battery					0-100
ph							0-14

�������ʲ���Ҫ̫�죬ƽ̨���Ҳ��4s����һ��

*/

//���豸��������
void DX511_Publish_Sub_Data(float gps_n, float gps_e, float ntu, int tds, float temp, int battery, float ph)
{
	char Json[350];

        snprintf(Json, sizeof(Json),
            "{\"id\": \"17785\", \"version\": \"1.0\", \"params\": [{\"properties\": {\"GPS_N\": {\"value\": %0.1f},\"GPS_E\": {\"value\": %0.1f},\"NTU\": {\"value\": %0.1f},\"TDS\": {\"value\": %d},\"Temperature\": {\"value\": %0.1f},\"battery\": {\"value\": %d},\"pH\": {\"value\": %0.1f}}, \"events\":{} , \"identity\": {\"productID\": \"9YyMBQhEkr\", \"deviceName\": \"Node0\"}}]}",  // ????????
            gps_n, gps_e, ntu, tds, temp, battery, ph
        );
				DX511_Publish("$sys/87D45T0g17/H750/thing/pack/post", Json, "SUCCESS");

}

extern TaskHandle_t NetWork_taskhandle;
extern TaskHandle_t ReciveOneNetData_taskhandle;



//30sһ��
void DX511_Ping(void)
{
	if(DX511_SendCmd("AT+MQTTSTATU\r\n","+MQTTSTATU: 0\r\n")==0)
	{
			snprintf(node_connect,sizeof(node_connect),"NetWork:NC");
			printf("��������Ͽ�����\r\n");
			 
			//�����������
			vTaskSuspend(NetWork_taskhandle);
			vTaskSuspend(ReciveOneNetData_taskhandle);
			//DX511_NetWork_Config();
			DX511_NetWork_Connect();
			vTaskResume(NetWork_taskhandle);
			vTaskResume(ReciveOneNetData_taskhandle);
	}
	else
	{
		printf("������������\r\n");
	}
	

}


//Ӧ����ͨ�������е�whileѭ����������
/*
ǰ���нṹ�嶨�����
while(1)
{
	if(DX511_GetData(200)!=NULL)
			{
				printf("NTU_H=%d\r\n",SettingData.NTU_H);
				printf("PH_H=%0.1f\r\n",SettingData.PH_H);
				printf("PH_L=%0.1f\r\n",SettingData.PH_L);
				printf("TDS_H=%d\r\n",SettingData.TDS_H);
				printf("Temperature_H=%0.1f\r\n",SettingData.Temperature_H);
				printf("Temperature_L=%0.1f\r\n",SettingData.Temperature_L);
			}
}
*/

unsigned char* DX511_GetData(unsigned short timeOut) {
    char* ptr = NULL;
    char* params_start = NULL;
		
    do {
        if (DX511_WaitRecive() == REV_OK) {
            // �״ζ�λ�����ݰ���ʼλ��
            ptr = strstr((char*)DX511_buf, "+MSUB:");
            if (!ptr) continue;

            // ���ζ�λparams������ʼ
            params_start = strstr(ptr, "\"params\":{");
            if (!params_start) return NULL;
            ptr = params_start;

            // ԭ�Ӳ���
            PARSE_INT_FIELD("NTU_H", SettingData.NTU_H);
            PARSE_INT_FIELD("PH_H", SettingData.PH_H);
            PARSE_INT_FIELD("PH_L", SettingData.PH_L);
            PARSE_INT_FIELD("TDS_H", SettingData.TDS_H);
            PARSE_INT_FIELD("Temperature_H", SettingData.Temperature_H);
            PARSE_INT_FIELD("Temperature_L", SettingData.Temperature_L);
						//xQueueOverwrite(xSettingDataQueue, &SettingData);
						printf("%d\r\n",SettingData.Temperature_L);
            return "OK";
        }
        vTaskDelay(5);
    } while (timeOut--);

    return NULL;
}

//��ȡʱ����Ӧ
int ParseTimeResponse(const char* response, RealTime* time) {
    int year, month, day, hour, minute, second;
    
    // ����sscanf��ȡ����
    if (sscanf(response, "+QNTP: 0,\"%04d/%02d/%02d,%02d:%02d:%02d",
               &year, &month, &day,
               &hour, &minute, &second) != 6) {
        return 0;
    }

    // �����ȡʱ���Ƿ���ȷ
    if (month < 1 || month > 12 ||
        day < 1 || day > 31 ||
        hour > 23 ||
        minute > 59 ||
        second > 59) {
        return 0;
    }

    time->year   = year;
    time->month  = month;
    time->day    = day;
    time->hour   = hour;
    time->minute = minute;
    time->second = second;

    return 1;
}


//ͨ�������Ʒ��������±���ʱ��
void DX511_GetTimeUpdate(void) {
    unsigned char timeout = 50;  // 5?(50*100ms)
    uint8_t retry_count = 3;
    RealTime rtc_time;
    while (retry_count--) {
        Usart_SendString(&huart2, 
                        (unsigned char *)"AT+QNTP=1,\"203.107.6.88\",123,1\r\n",
                        strlen("AT+QNTP=1,\"203.107.6.88\",123,1\r\n"));
        
        for (uint8_t i = 0; i < timeout; i++) {
            if (DX511_WaitRecive() == REV_OK) {
                char* ptr = strstr((char*)DX511_buf, "+QNTP: 0,\"");
                if (ptr && ParseTimeResponse(ptr, &rtc_time)) {
										xQueueOverwrite(xTimeUpdateQueue, &rtc_time);		//���»�ȡ����ʱ���ֵ
                    DX511_Clear();
                    return;
                }
                DX511_Clear();
            }
            vTaskDelay(100); 
        }
    }
}






void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart == &huart2)//DX511������ƽ̨����
		{
			if(DX511_cnt >= sizeof(DX511_buf)-1)
			{            
				DX511_cnt = 0; //��ֹ���ڱ�ˢ��
			}
			DX511_buf[DX511_cnt++] = UART_RX_Buf;

			HAL_UART_Receive_IT(&huart2,(uint8_t *)&UART_RX_Buf, 1); //&ȡ��ַ
		}
		
		
		else if(huart == &huart3)//Lora������λ��������
		{
			if(LoRa_cnt >= sizeof(LoRa_buf)-1)
			{            
				LoRa_cnt = 0; //��ֹ���ڱ�ˢ��
			}
			LoRa_buf[LoRa_cnt++] = UART3_RX_Buf;

			HAL_UART_Receive_IT(&huart3,(uint8_t *)&UART3_RX_Buf, 1); //&ȡ��ַ
		
		}
}





