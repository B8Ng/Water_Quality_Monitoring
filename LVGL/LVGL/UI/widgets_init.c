/*
* Copyright 2025 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "lvgl.h"
#include "gui_guider.h"
#include "widgets_init.h"
#include <stdlib.h>
#include <string.h>
#include "Lora.h"
#include <stdio.h>

__attribute__((unused)) void kb_event_cb (lv_event_t *e) {
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *kb = lv_event_get_target(e);
    if(code == LV_EVENT_READY || code == LV_EVENT_CANCEL) {
        lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
    }
}

__attribute__((unused)) void ta_event_cb (lv_event_t *e) {
    lv_event_code_t code = lv_event_get_code(e);
#if LV_USE_KEYBOARD || LV_USE_ZH_KEYBOARD
    lv_obj_t *ta = lv_event_get_target(e);
#endif
    lv_obj_t *kb = lv_event_get_user_data(e);
    if (code == LV_EVENT_FOCUSED || code == LV_EVENT_CLICKED)
    {
#if LV_USE_ZH_KEYBOARD != 0
        lv_zh_keyboard_set_textarea(kb, ta);
#endif
#if LV_USE_KEYBOARD != 0
        lv_keyboard_set_textarea(kb, ta);
#endif
        lv_obj_move_foreground(kb);
        lv_obj_clear_flag(kb, LV_OBJ_FLAG_HIDDEN);
    }
    if (code == LV_EVENT_CANCEL || code == LV_EVENT_DEFOCUSED)
    {

#if LV_USE_ZH_KEYBOARD != 0
        lv_zh_keyboard_set_textarea(kb, ta);
#endif
#if LV_USE_KEYBOARD != 0
        lv_keyboard_set_textarea(kb, ta);
#endif
        lv_obj_move_background(kb);
        lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
    }
}

#if LV_USE_ANALOGCLOCK != 0
void clock_count(int *hour, int *min, int *sec)
{
    (*sec)++;
    if(*sec == 60)
    {
        *sec = 0;
        (*min)++;
    }
    if(*min == 60)
    {
        *min = 0;
        if(*hour < 12)
        {
            (*hour)++;
        } else {
            (*hour)++;
            *hour = *hour %12;
        }
    }
}
#endif


extern int MainUI_digital_clock_1_hour_value;
extern int MainUI_digital_clock_1_min_value;
extern int MainUI_digital_clock_1_sec_value;
extern char node_num[13];
extern char node_connect[13];
extern char dimness[12];				//NodeUI和DetailUI需要用来刷新
extern char temp[8];
extern char tds[9];
extern char ph[9];
extern char gps[20];
extern char lora[16];

extern SubData device_data;
extern char warning[12];

extern lv_obj_t *Log_log_win_label;

extern char warning_log[1024];

void MainUI_digital_clock_1_timer(lv_timer_t *timer)
{
    clock_count_24(&MainUI_digital_clock_1_hour_value, &MainUI_digital_clock_1_min_value, &MainUI_digital_clock_1_sec_value);
    if (lv_obj_is_valid(guider_ui.MainUI_digital_clock_1))
    {
      lv_dclock_set_text_fmt(guider_ui.MainUI_digital_clock_1, "%d:%02d", MainUI_digital_clock_1_hour_value, MainUI_digital_clock_1_min_value);

			lv_label_set_text(guider_ui.MainUI_connect,node_connect);
			lv_label_set_text(guider_ui.MainUI_node_num, node_num);
			
    }
		if(lv_obj_is_valid(guider_ui.MainUI_log))
		{
			lv_label_set_text(guider_ui.MainUI_log,warning);
		}
		if(lv_obj_is_valid(guider_ui.NodeUI_log))
		{
			lv_label_set_text(guider_ui.NodeUI_log, warning);
		}
		if(lv_obj_is_valid(guider_ui.DetailUI_log_label))
		{
			lv_label_set_text(guider_ui.DetailUI_log_label,warning);
		}
		if(lv_obj_is_valid(guider_ui.Log_log_win))
		{
			lv_label_set_text(Log_log_win_label,warning_log);
			
		}
}


void SubData_timer(lv_timer_t *timer)
{
	if(lv_obj_is_valid(guider_ui.NodeUI_dimness))	//判断这个ntu是否还存在
	{
		lv_label_set_text(guider_ui.NodeUI_dimness,dimness);
		lv_label_set_text(guider_ui.NodeUI_temperature,temp);
		lv_label_set_text(guider_ui.NodeUI_tds,tds);
		lv_label_set_text(guider_ui.NodeUI_ph_label,ph);
		lv_label_set_text(guider_ui.NodeUI_GPS,gps);
		lv_label_set_text(guider_ui.NodeUI_LoRaConnect,lora);
	}
	if(lv_obj_is_valid(guider_ui.DetailUI_ntu))		//细节更新	可以用来写历史更新
	{
		lv_label_set_text(guider_ui.DetailUI_tds,tds);
		lv_label_set_text(guider_ui.DetailUI_ntu,dimness);
		lv_label_set_text(guider_ui.DetailUI_gps,gps);
		lv_label_set_text(guider_ui.DetailUI_ph_label,ph);
		lv_label_set_text(guider_ui.DetailUI_temperature,temp);
	}


	

	
}
//历史数据更新
void SubData_history_timer(lv_timer_t *timer)
{
	if(lv_obj_is_valid(guider_ui.DetailUI_history))	//如果这个表格控件存在的话
	{
		//要先判断是否有这个控件
						
		lv_chart_set_next_value(guider_ui.DetailUI_history, guider_ui.DetailUI_history_0, (lv_coord_t)(device_data.ph * 10));
    
    // TDS
    lv_chart_set_next_value(guider_ui.DetailUI_history, guider_ui.DetailUI_history_1, (lv_coord_t)device_data.tds);
    
    // temp
    lv_chart_set_next_value(guider_ui.DetailUI_history, guider_ui.DetailUI_history_2, (lv_coord_t)(device_data.temp + 40));
    
    // NTU
    lv_chart_set_next_value(guider_ui.DetailUI_history, guider_ui.DetailUI_history_3, (lv_coord_t)device_data.ntu);
	}
}


