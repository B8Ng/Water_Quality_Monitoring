/*
* Copyright 2025 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "events_init.h"
#include <stdio.h>
#include "lvgl.h"
#include "DX511.h"
#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"

#if LV_USE_GUIDER_SIMULATOR && LV_USE_FREEMASTER
#include "freemaster_client.h"
#endif


static void MainUI_Node_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
				setup_scr_NodeUI(&guider_ui);
				lv_scr_load_anim(guider_ui.NodeUI,LV_SCR_LOAD_ANIM_FADE_ON,200,0,true);
        //ui_load_scr_animation(&guider_ui, &guider_ui.NodeUI, guider_ui.NodeUI_del, &guider_ui.MainUI_del, setup_scr_NodeUI, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true, true);
        break;
    }
    default:
        break;
    }
}

static void MainUI_Settingicon_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_RELEASED:
    {

				setup_scr_Settings(&guider_ui);
				lv_scr_load_anim(guider_ui.Settings,LV_SCR_LOAD_ANIM_FADE_ON,200,0,true);
        //ui_load_scr_animation(&guider_ui, &guider_ui.Settings, guider_ui.Settings_del, &guider_ui.MainUI_del, setup_scr_Settings, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true, true);
        break;
    }
    default:
        break;
    }
}

void events_init_MainUI (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->MainUI_Node, MainUI_Node_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->MainUI_Settingicon, MainUI_Settingicon_event_handler, LV_EVENT_ALL, ui);
}

static void Settings_About_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
				setup_scr_About(&guider_ui);
				lv_scr_load_anim(guider_ui.About,LV_SCR_LOAD_ANIM_FADE_ON,200,0,true);
        //ui_load_scr_animation(&guider_ui, &guider_ui.About, guider_ui.About_del, &guider_ui.Settings_del, setup_scr_About, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true, true);
        break;
    }
    default:
        break;
    }
}



static void Settings_backButton_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
				setup_scr_MainUI(&guider_ui);
				lv_scr_load_anim(guider_ui.MainUI,LV_SCR_LOAD_ANIM_FADE_ON,200,0,true);
        //ui_load_scr_animation(&guider_ui, &guider_ui.MainUI, guider_ui.MainUI_del, &guider_ui.Settings_del, setup_scr_MainUI, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true, true);
			//ui_load_scr_animation(&guider_ui, &guider_ui.MainUI, guider_ui.MainUI_del, &guider_ui.Settings_del, setup_scr_MainUI, LV_SCR_LOAD_ANIM_NONE, 200, 200, true, true);
        break;
    }
    default:
        break;
    }
}

void events_init_Settings (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->Settings_About, Settings_About_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->Settings_backButton, Settings_backButton_event_handler, LV_EVENT_ALL, ui);
}

static void About_About_button_back_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {		
				setup_scr_Settings(&guider_ui);
				lv_scr_load_anim(guider_ui.Settings,LV_SCR_LOAD_ANIM_FADE_ON,200,0,true);
        //ui_load_scr_animation(&guider_ui, &guider_ui.Settings, guider_ui.Settings_del, &guider_ui.About_del, setup_scr_Settings, LV_SCR_LOAD_ANIM_FADE_ON, 100, 100, true, true);
        break;
    }
    default:
        break;
    }
}

void events_init_About (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->About_About_button_back, About_About_button_back_event_handler, LV_EVENT_ALL, ui);
}

static void NodeUI_back_button_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {	
				setup_scr_MainUI(&guider_ui);
				lv_scr_load_anim(guider_ui.MainUI,LV_SCR_LOAD_ANIM_FADE_ON,200,0,true);
        //ui_load_scr_animation(&guider_ui, &guider_ui.MainUI, guider_ui.MainUI_del, &guider_ui.NodeUI_del, setup_scr_MainUI, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true, true);
        break;
    }
    default:
        break;
    }
}

static void NodeUI_node_obj_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
				setup_scr_DetailUI(&guider_ui);
				lv_scr_load_anim(guider_ui.DetailUI,LV_SCR_LOAD_ANIM_FADE_ON,200,0,true);
        //ui_load_scr_animation(&guider_ui, &guider_ui.DetailUI, guider_ui.DetailUI_del, &guider_ui.NodeUI_del, setup_scr_DetailUI, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true, true);
        break;
    }
    default:
        break;
    }
}

static void NodeUI_battery_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_VALUE_CHANGED:
    {

        break;
    }
    default:
        break;
    }
}

void events_init_NodeUI (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->NodeUI_back_button, NodeUI_back_button_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->NodeUI_node_obj, NodeUI_node_obj_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->NodeUI_battery, NodeUI_battery_event_handler, LV_EVENT_ALL, ui);
}

static void DetailUI_back_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
				setup_scr_NodeUI(&guider_ui);
				lv_scr_load_anim(guider_ui.NodeUI,LV_SCR_LOAD_ANIM_FADE_ON,200,0,true);
        //ui_load_scr_animation(&guider_ui, &guider_ui.NodeUI, guider_ui.NodeUI_del, &guider_ui.DetailUI_del, setup_scr_NodeUI, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true, true);
        break;
    }
    default:
        break;
    }
}

static void DetailUI_th_setting_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
				setup_scr_TH_Settings(&guider_ui);
				lv_scr_load_anim(guider_ui.TH_Settings,LV_SCR_LOAD_ANIM_FADE_ON,200,0,true);
        //ui_load_scr_animation(&guider_ui, &guider_ui.TH_Settings, guider_ui.TH_Settings_del, &guider_ui.DetailUI_del, setup_scr_TH_Settings, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true, true);
        break;
    }
    default:
        break;
    }
}

static void DetailUI_log_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
				setup_scr_Log(&guider_ui);
				lv_scr_load_anim(guider_ui.Log,LV_SCR_LOAD_ANIM_MOVE_TOP,200,0,true);
        //ui_load_scr_animation(&guider_ui, &guider_ui.Log, guider_ui.Log_del, &guider_ui.DetailUI_del, setup_scr_Log, LV_SCR_LOAD_ANIM_MOVE_TOP, 200, 200, true, true);
        break;
    }
    default:
        break;
    }
}

void events_init_DetailUI (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->DetailUI_back, DetailUI_back_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->DetailUI_th_setting, DetailUI_th_setting_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->DetailUI_log, DetailUI_log_event_handler, LV_EVENT_ALL, ui);
}

static void TH_Settings_back_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
				setup_scr_DetailUI(&guider_ui);
				lv_scr_load_anim(guider_ui.DetailUI,LV_SCR_LOAD_ANIM_FADE_ON,200,0,true);
        //ui_load_scr_animation(&guider_ui, &guider_ui.DetailUI, guider_ui.DetailUI_del, &guider_ui.TH_Settings_del, setup_scr_DetailUI, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true, true);
        break;
    }
    default:
        break;
    }
}

static const int temperature_options[] = {-20, -15, -10, -5, 0, 5, 10, 15, 20, 25, 30, 40, 50, 60};
//返回温度值的索引
int temperature_to_index(float temp) {
    const int option_count = sizeof(temperature_options) / sizeof(temperature_options[0]);
    for (int i = 0; i < option_count; i++) {
        if (temp == temperature_options[i]) {
            return i;
        }
    }

    return 0; 
}



//int get_tds_value(int index) {
//		static const int tds_options[] = {100, 200, 300, 400, 500, 600, 700, 800, 900, 1000};
//    const int option_count = sizeof(tds_options) / sizeof(tds_options[0]);
//    if (index >= 0 && index < option_count) {
//        return tds_options[index];
//    }
//    return 0;
//}



extern SensorSettingData SettingData;
static void TH_Settings_save_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {	
				//更新数据给设置数据上传
				//DX511_Publish_GateWay_Setting(int NTU_H,float PH_H,float PH_L,int TDS_H,float Temperature_H,float Temperature_L)
				
				//把表单的数据给他还要
				SettingData.NTU_H = lv_dropdown_get_selected(guider_ui.TH_Settings_highddlist_4);		//获取表单的NTU
			

        int tds_index = lv_dropdown_get_selected(guider_ui.TH_Settings_highlist_2);
				printf("tds:%d\r\n",tds_index);
        SettingData.TDS_H = ((tds_index*100)+100);
				printf("tds:%d\r\n",SettingData.TDS_H);
				SettingData.PH_L = lv_dropdown_get_selected(guider_ui.TH_Settings_lowlist);
				SettingData.PH_H = lv_dropdown_get_selected(guider_ui.TH_Settings_high_list);
				
				//SettingData.TDS_H = lv_dropdown_get_selected(guider_ui.TH_Settings_highlist_2);
			
				int high_temp_index = lv_dropdown_get_selected(guider_ui.TH_Settings_highddlist_3);
        SettingData.Temperature_H = temperature_options[high_temp_index];

        int low_temp_index = lv_dropdown_get_selected(guider_ui.TH_Settings_lowddlist_3);
        SettingData.Temperature_L = temperature_options[low_temp_index];
				
				 printf("Saved Settings:\n"
               "PH: %d-%d\n"
               "TDS: %d\n"
               "Temp: %d-%d\n"
               "NTU: %d\n",
               SettingData.PH_L,
               SettingData.PH_H,
               SettingData.TDS_H,
               SettingData.Temperature_L,
               SettingData.Temperature_H,
               SettingData.NTU_H);
				if(SettingData.PH_H < SettingData.PH_L){
					printf("PH值范围错误！\r\n");
					float temp = SettingData.PH_H;
					SettingData.PH_H = SettingData.PH_L;
					SettingData.PH_L = temp;
				}
				
				if(SettingData.Temperature_H < SettingData.Temperature_L){
					printf("温度值范围错误！\r\n");
					float temp = SettingData.Temperature_H;
					SettingData.Temperature_H = SettingData.Temperature_L;
					SettingData.Temperature_L = temp;
				}
				//如果想打磨细节就把数据更新回去表单
				
				DX511_Publish_GateWay_Setting(SettingData.NTU_H,SettingData.PH_H,SettingData.PH_L,SettingData.TDS_H,SettingData.Temperature_H,SettingData.Temperature_L);
        
				setup_scr_DetailUI(&guider_ui);
				lv_scr_load_anim(guider_ui.DetailUI,LV_SCR_LOAD_ANIM_FADE_ON,200,0,true);
				//ui_load_scr_animation(&guider_ui, &guider_ui.DetailUI, guider_ui.DetailUI_del, &guider_ui.TH_Settings_del, setup_scr_DetailUI, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true, true);
        break;
    }
    default:
        break;
    }
}

void events_init_TH_Settings (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->TH_Settings_back, TH_Settings_back_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->TH_Settings_save, TH_Settings_save_event_handler, LV_EVENT_ALL, ui);
}

static void Log_log_win_item0_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
				setup_scr_DetailUI(&guider_ui);
				lv_scr_load_anim(guider_ui.DetailUI,LV_SCR_LOAD_ANIM_MOVE_BOTTOM,200,0,true);
        //ui_load_scr_animation(&guider_ui, &guider_ui.DetailUI, guider_ui.DetailUI_del, &guider_ui.Log_del, setup_scr_DetailUI, LV_SCR_LOAD_ANIM_MOVE_BOTTOM, 200, 200, true, true);
        break;
    }
    default:
        break;
    }
}

void events_init_Log (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->Log_log_win_item0, Log_log_win_item0_event_handler, LV_EVENT_ALL, ui);
}


void events_init(lv_ui *ui)
{

}
