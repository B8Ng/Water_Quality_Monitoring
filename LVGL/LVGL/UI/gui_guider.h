/*
* Copyright 2025 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#ifndef GUI_GUIDER_H
#define GUI_GUIDER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

typedef struct
{
  
	lv_obj_t *MainUI;
	bool MainUI_del;
	lv_obj_t *MainUI_cont_1;
	lv_obj_t *MainUI_Node;
	lv_obj_t *MainUI_img_1;
	lv_obj_t *MainUI_node_num;
	lv_obj_t *MainUI_connect;
	lv_obj_t *MainUI_log;
	lv_obj_t *MainUI_Settingicon;
	lv_obj_t *MainUI_Settingicon_label;
	lv_obj_t *MainUI_digital_clock_1;
	lv_obj_t *Settings;
	bool Settings_del;
	lv_obj_t *Settings_Slider;
	lv_obj_t *Settings_LightChange;
	lv_obj_t *Settings_slider_1;
	lv_obj_t *Settings_label_1;
	lv_obj_t *Settings_About;
	lv_obj_t *Settings_label_2;
	lv_obj_t *Settings_SettingTitle;
	lv_obj_t *Settings_backButton;
	lv_obj_t *Settings_backButton_label;
	lv_obj_t *About;
	bool About_del;
	lv_obj_t *About_Slider;
	lv_obj_t *About_AboutText;
	lv_obj_t *About_label_1;
	lv_obj_t *About_AboutTitle;
	lv_obj_t *About_About_button_back;
	lv_obj_t *About_About_button_back_label;
	lv_obj_t *NodeUI;
	bool NodeUI_del;
	lv_obj_t *NodeUI_cont_1;
	lv_obj_t *NodeUI_back_button;
	lv_obj_t *NodeUI_back_button_label;
	lv_obj_t *NodeUI_table;
	lv_obj_t *NodeUI_node_obj;
	lv_obj_t *NodeUI_node_img;
	lv_obj_t *NodeUI_node_num;
	lv_obj_t *NodeUI_LoRaConnect;
	lv_obj_t *NodeUI_battery;
	lv_obj_t *NodeUI_GPS;
	lv_obj_t *NodeUI_log;
	lv_obj_t *NodeUI_ph_label;
	lv_obj_t *NodeUI_tds;
	lv_obj_t *NodeUI_temperature;
	lv_obj_t *NodeUI_dimness;
	lv_obj_t *DetailUI;
	bool DetailUI_del;
	lv_obj_t *DetailUI_title;
	lv_obj_t *DetailUI_back;
	lv_obj_t *DetailUI_back_label;
	lv_obj_t *DetailUI_th_setting;
	lv_obj_t *DetailUI_th_setting_label;
	lv_obj_t *DetailUI_table;
	lv_obj_t *DetailUI_history;
	lv_chart_series_t *DetailUI_history_0;
	lv_chart_series_t *DetailUI_history_1;
	lv_chart_series_t *DetailUI_history_2;
	lv_chart_series_t *DetailUI_history_3;
	lv_obj_t *DetailUI_node_detail;
	lv_obj_t *DetailUI_node_img;
	lv_obj_t *DetailUI_node_num;
	lv_obj_t *DetailUI_battery;
	lv_obj_t *DetailUI_gps;
	lv_obj_t *DetailUI_ph_label;
	lv_obj_t *DetailUI_tds;
	lv_obj_t *DetailUI_temperature;
	lv_obj_t *DetailUI_ntu;
	lv_obj_t *DetailUI_log;
	lv_obj_t *DetailUI_log_label;
	lv_obj_t *TH_Settings;
	bool TH_Settings_del;
	lv_obj_t *TH_Settings_cont_1;
	lv_obj_t *TH_Settings_back;
	lv_obj_t *TH_Settings_back_label;
	lv_obj_t *TH_Settings_save;
	lv_obj_t *TH_Settings_save_label;
	lv_obj_t *TH_Settings_Setting;
	lv_obj_t *TH_Settings_ph_label;
	lv_obj_t *TH_Settings_high;
	lv_obj_t *TH_Settings_lowlist;
	lv_obj_t *TH_Settings_high_list;
	lv_obj_t *TH_Settings_ph_l;
	lv_obj_t *TH_Settings_low;
	lv_obj_t *TH_Settings_TDS;
	lv_obj_t *TH_Settings_highlist_2;
	lv_obj_t *TH_Settings_tds;
	lv_obj_t *TH_Settings_T_lable;
	lv_obj_t *TH_Settings_highlabel_3;
	lv_obj_t *TH_Settings_lowddlist_3;
	lv_obj_t *TH_Settings_Temperature;
	lv_obj_t *TH_Settings_lowlabel_3;
	lv_obj_t *TH_Settings_highddlist_3;
	lv_obj_t *TH_Settings_NTU;
	lv_obj_t *TH_Settings_highddlist_4;
	lv_obj_t *TH_Settings_ntu;
	lv_obj_t *Log;
	bool Log_del;
	lv_obj_t *Log_log_win;
	lv_obj_t *Log_log_win_item0;
}lv_ui;

typedef void (*ui_setup_scr_t)(lv_ui * ui);

void ui_init_style(lv_style_t * style);

void ui_load_scr_animation(lv_ui *ui, lv_obj_t ** new_scr, bool new_scr_del, bool * old_scr_del, ui_setup_scr_t setup_scr,
                           lv_scr_load_anim_t anim_type, uint32_t time, uint32_t delay, bool is_clean, bool auto_del);

void ui_animation(void * var, int32_t duration, int32_t delay, int32_t start_value, int32_t end_value, lv_anim_path_cb_t path_cb,
                       uint16_t repeat_cnt, uint32_t repeat_delay, uint32_t playback_time, uint32_t playback_delay,
                       lv_anim_exec_xcb_t exec_cb, lv_anim_start_cb_t start_cb, lv_anim_ready_cb_t ready_cb);


void init_scr_del_flag(lv_ui *ui);

void setup_ui(lv_ui *ui);

void init_keyboard(lv_ui *ui);

extern lv_ui guider_ui;


void setup_scr_MainUI(lv_ui *ui);
void setup_scr_Settings(lv_ui *ui);
void setup_scr_About(lv_ui *ui);
void setup_scr_NodeUI(lv_ui *ui);
void setup_scr_DetailUI(lv_ui *ui);
void setup_scr_TH_Settings(lv_ui *ui);
void setup_scr_Log(lv_ui *ui);
LV_IMG_DECLARE(_node_alpha_32x32);
LV_IMG_DECLARE(_setting_alpha_32x32);
LV_IMG_DECLARE(_setting_alpha_32x32);
LV_IMG_DECLARE(_setting_alpha_32x32);
LV_IMG_DECLARE(_setting_alpha_32x32);
LV_IMG_DECLARE(_nodeb_alpha_32x32);
LV_IMG_DECLARE(_icon_dianchi_4_alpha_32x32);
LV_IMG_DECLARE(_nodeb_alpha_32x32);
LV_IMG_DECLARE(_icon_dianchi_4_alpha_32x32);

LV_FONT_DECLARE(lv_font_Acme_Regular_21)
LV_FONT_DECLARE(lv_font_montserratMedium_16)
LV_FONT_DECLARE(lv_font_montserratMedium_12)
LV_FONT_DECLARE(lv_font_Acme_Regular_80)
LV_FONT_DECLARE(lv_font_montserratMedium_20)
LV_FONT_DECLARE(lv_font_montserratMedium_21)
LV_FONT_DECLARE(lv_font_montserratMedium_18)


#ifdef __cplusplus
}
#endif
#endif
