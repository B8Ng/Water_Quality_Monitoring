#ifndef 	__DX511_H
#define 	__DX511_H

#define REV_OK		0	//接收完成标志
#define REV_WAIT	1	//接收未完成标志
	
//设置数据结构体
typedef struct {
    int NTU_H;
    int PH_H;
    int PH_L;
    int TDS_H;
    int Temperature_H;
    int Temperature_L;
} SensorSettingData;

//网络获取时间结构体
typedef struct {
    int year;  
    int month;  
    int day;   
    int hour;   
    int minute; 
    int second;
} RealTime;


//提取关键字宏
#define PARSE_INT_FIELD(field_name, target) \
    do { \
        char* _ptr = strstr(ptr, "\"" field_name "\":"); \
        if (_ptr) { \
            _ptr += strlen("\"" field_name "\":"); \
            target = atoi(_ptr); \
        } \
    } while(0)

#define PARSE_FLOAT_FIELD(field_name, target) \
    do { \
        char* _ptr = strstr(ptr, "\"" field_name "\":"); \
        if (_ptr) { \
            _ptr += strlen("\"" field_name "\":"); \
            target = atof(_ptr); \
        } \
    } while(0)


	
void DX511_Init(void);
void DX511_ON(void);
void DX511_OFF(void);
void DX511_Clear(void);
_Bool DX511_WaitRecive(void);
_Bool DX511_SendCmd(char *cmd, char *res);
void DX511_NetWork_Config(void);
void DX511_NetWork_Connect(void);


void DX511_Publish(char *topic, char *Json, char *res);

void DX511_NetWork_Sub_Number(void);
void DX511_NetWork_Sub_Connect(void);
void DX511_NetWork_Sub_Disconnect(void);
		
//void DX511_Publish_GateWay_Setting_New(int NTU_H,float PH_H,float PH_L,int TDS_H,float Temperature_H,float Temperature_L);
		void DX511_Publish_GateWay_Setting(int NTU_H,int PH_H,int PH_L,int TDS_H,int Temperature_H,int Temperature_L);
			
void DX511_Publish_Sub_Data(float gps_n, float gps_e, float ntu, int tds, float temp, int battery, float ph);

void DX511_Ping(void);

unsigned char *DX511_GetData(unsigned short timeOut);
void DX511_GetTimeUpdate(void);


#endif 
