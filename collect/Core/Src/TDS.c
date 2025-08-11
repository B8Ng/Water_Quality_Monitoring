#include "TDS.h"
#include "adc.h"
#include "ds18b20.h"
uint32_t ADC_convert_result[1];	//DMA��Ľ��
float temperature = 0;					//�¶�
#define VREF 2.4								//�ο���ѹ


//����TDS�ɼ�
void TDS_Start(void)
{
	HAL_ADCEx_Calibration_Start(&hadc1);
	HAL_ADC_Start_DMA(&hadc1, (uint32_t*)ADC_convert_result, 1);
}
//�ⲿ�ӿں�������ȡTDSֵ
uint32_t TDS_GetValue(void)
{
		 temperature = Temp_Value_Conversion();		//��ȡ�ο��¶�
		
		 float compensationCoefficient = 1.0 + 0.02 * (temperature - 25.0);
		 float compensationVolatge = (getMedianNum() * (float)VREF / 1024.0) / compensationCoefficient;
		 return (133.42 * compensationVolatge * compensationVolatge * compensationVolatge - 255.86 * compensationVolatge * compensationVolatge + 857.39 * compensationVolatge) * 0.5;
}

//��ȡ��ֵ�˲���ֵ
uint32_t getMedianNum(void)
{
	uint32_t temp_num[20];
  for (int i = 0; i < 20; i++)
    temp_num[i]= ADC_convert_result[0];
  uint32_t i, j, bTemp; 
  for (j = 0; j < 20 - 1; j++)
  {
    for (i = 0; i < 20 - j - 1; i++)
    {
      if (temp_num[i] > temp_num[i + 1])
      {
        bTemp = temp_num[i];
        temp_num[i] = temp_num[i + 1];
        temp_num[i + 1] = bTemp;
      }
    }
  }
  if ((20 & 1) > 0)
    bTemp = temp_num[(20 - 1) / 2];
  else
    bTemp = (temp_num[20 / 2] + temp_num[20 / 2 - 1]) / 2;
  return bTemp;
}
