#ifndef		__LORA_H
#define		__LORA_H
	
#include <stdint.h>
	
//���豸�ϱ�����
typedef struct	{
		float gps_n;
		float gps_e;
		float ntu;
		int tds;
		float temp;
		int battery;
		float ph;
}	SubData;

#define REV_OK		0	//������ɱ�־
#define REV_WAIT	1	//����δ��ɱ�־

void LoRa_Init(void);
void LoRa_Clear(void);
void LoRa_Try2GetData(uint8_t Device);

#endif
