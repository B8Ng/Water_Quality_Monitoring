#ifndef		__LORA_H
#define		__LORA_H
	
#include <stdint.h>
	
//子设备上报数据
typedef struct	{
		float gps_n;
		float gps_e;
		float ntu;
		int tds;
		float temp;
		int battery;
		float ph;
}	SubData;

#define REV_OK		0	//接收完成标志
#define REV_WAIT	1	//接收未完成标志

void LoRa_Init(void);
void LoRa_Clear(void);
void LoRa_Try2GetData(uint8_t Device);

#endif
