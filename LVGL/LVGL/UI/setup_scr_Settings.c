/*
* Copyright 2025 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "widgets_init.h"
#include "lcd_pwm.h"

static void brightness_slider_event_cb(lv_event_t * e);

void setup_scr_Settings(lv_ui *ui)
{
    //Write codes Settings
    ui->Settings = lv_obj_create(NULL);
    lv_obj_set_size(ui->Settings, 480, 272);
    lv_obj_set_scrollbar_mode(ui->Settings, LV_SCROLLBAR_MODE_OFF);

    //Write style for Settings, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Settings, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Settings_Slider
    ui->Settings_Slider = lv_obj_create(ui->Settings);
    lv_obj_set_pos(ui->Settings_Slider, 0, 50);
    lv_obj_set_size(ui->Settings_Slider, 480, 222);
    lv_obj_set_scrollbar_mode(ui->Settings_Slider, LV_SCROLLBAR_MODE_AUTO);

    //Write style for Settings_Slider, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Settings_Slider, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Settings_Slider, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Settings_Slider, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Settings_Slider, lv_color_hex(0xe2e2e2), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->Settings_Slider, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Settings_Slider, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Settings_Slider, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Settings_Slider, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Settings_Slider, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Settings_Slider, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Settings_LightChange
    ui->Settings_LightChange = lv_obj_create(ui->Settings_Slider);
    lv_obj_set_pos(ui->Settings_LightChange, 7, 5);
    lv_obj_set_size(ui->Settings_LightChange, 465, 50);
    lv_obj_set_scrollbar_mode(ui->Settings_LightChange, LV_SCROLLBAR_MODE_OFF);

    //Write style for Settings_LightChange, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Settings_LightChange, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Settings_LightChange, 12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Settings_LightChange, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Settings_LightChange, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->Settings_LightChange, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Settings_LightChange, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Settings_LightChange, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Settings_LightChange, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Settings_LightChange, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Settings_LightChange, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Settings_slider_1
    ui->Settings_slider_1 = lv_slider_create(ui->Settings_LightChange);
    lv_slider_set_range(ui->Settings_slider_1, 0, 100);
    lv_slider_set_mode(ui->Settings_slider_1, LV_SLIDER_MODE_NORMAL);
    lv_slider_set_value(ui->Settings_slider_1, LCD_PwmGetPulse(), LV_ANIM_OFF);			//读取初始化后占空比值
    lv_obj_set_pos(ui->Settings_slider_1, 147, 21);
    lv_obj_set_size(ui->Settings_slider_1, 300, 8);
		//调节亮度回调函数
		lv_obj_add_event_cb(ui->Settings_slider_1, brightness_slider_event_cb, LV_EVENT_VALUE_CHANGED, ui);

    //Write style for Settings_slider_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Settings_slider_1, 60, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Settings_slider_1, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->Settings_slider_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Settings_slider_1, 50, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui->Settings_slider_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Settings_slider_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for Settings_slider_1, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Settings_slider_1, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Settings_slider_1, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->Settings_slider_1, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Settings_slider_1, 50, LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //Write style for Settings_slider_1, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Settings_slider_1, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Settings_slider_1, lv_color_hex(0x2195f6), LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->Settings_slider_1, LV_GRAD_DIR_NONE, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Settings_slider_1, 50, LV_PART_KNOB|LV_STATE_DEFAULT);

    //Write codes Settings_label_1
    ui->Settings_label_1 = lv_label_create(ui->Settings_LightChange);
    lv_label_set_text(ui->Settings_label_1, "Brightness");
    lv_label_set_long_mode(ui->Settings_label_1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->Settings_label_1, 15, 16);
    lv_obj_set_size(ui->Settings_label_1, 106, 18);

    //Write style for Settings_label_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Settings_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Settings_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Settings_label_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Settings_label_1, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->Settings_label_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->Settings_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->Settings_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Settings_label_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Settings_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Settings_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Settings_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Settings_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Settings_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Settings_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Settings_About
    ui->Settings_About = lv_obj_create(ui->Settings_Slider);
    lv_obj_set_pos(ui->Settings_About, 7, 63);
    lv_obj_set_size(ui->Settings_About, 465, 50);
    lv_obj_set_scrollbar_mode(ui->Settings_About, LV_SCROLLBAR_MODE_OFF);

    //Write style for Settings_About, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Settings_About, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Settings_About, 12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Settings_About, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Settings_About, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->Settings_About, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Settings_About, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Settings_About, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Settings_About, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Settings_About, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Settings_About, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Settings_label_2
    ui->Settings_label_2 = lv_label_create(ui->Settings_About);
    lv_label_set_text(ui->Settings_label_2, "About");
    lv_label_set_long_mode(ui->Settings_label_2, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->Settings_label_2, 15, 16);
    lv_obj_set_size(ui->Settings_label_2, 106, 18);

    //Write style for Settings_label_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Settings_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Settings_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Settings_label_2, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Settings_label_2, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->Settings_label_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->Settings_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->Settings_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Settings_label_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Settings_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Settings_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Settings_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Settings_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Settings_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Settings_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Settings_SettingTitle
    ui->Settings_SettingTitle = lv_obj_create(ui->Settings);
    lv_obj_set_pos(ui->Settings_SettingTitle, 0, 0);
    lv_obj_set_size(ui->Settings_SettingTitle, 480, 50);
    lv_obj_set_scrollbar_mode(ui->Settings_SettingTitle, LV_SCROLLBAR_MODE_OFF);

    //Write style for Settings_SettingTitle, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Settings_SettingTitle, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Settings_SettingTitle, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Settings_SettingTitle, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Settings_SettingTitle, lv_color_hex(0x62b4e4), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->Settings_SettingTitle, LV_GRAD_DIR_HOR, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui->Settings_SettingTitle, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_main_stop(ui->Settings_SettingTitle, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_stop(ui->Settings_SettingTitle, 177, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Settings_SettingTitle, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Settings_SettingTitle, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Settings_SettingTitle, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Settings_SettingTitle, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Settings_SettingTitle, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Settings_backButton
    ui->Settings_backButton = lv_btn_create(ui->Settings_SettingTitle);
    ui->Settings_backButton_label = lv_label_create(ui->Settings_backButton);
    lv_label_set_text(ui->Settings_backButton_label, "Back");
    lv_label_set_long_mode(ui->Settings_backButton_label, LV_LABEL_LONG_SCROLL);
    lv_obj_align(ui->Settings_backButton_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->Settings_backButton, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->Settings_backButton_label, LV_PCT(100));
    lv_obj_set_pos(ui->Settings_backButton, 13, 6);
    lv_obj_set_size(ui->Settings_backButton, 87, 34);

    //Write style for Settings_backButton, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Settings_backButton, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Settings_backButton, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->Settings_backButton, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->Settings_backButton, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Settings_backButton, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Settings_backButton, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Settings_backButton, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Settings_backButton, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->Settings_backButton, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Settings_backButton, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of Settings.


    //Update current screen layout.
    lv_obj_update_layout(ui->Settings);

    //Init events for screen.
    events_init_Settings(ui);
}


//调节亮度回调函数
static void brightness_slider_event_cb(lv_event_t * e)
{
    lv_obj_t * slider = lv_event_get_target(e);
    int32_t brightness = lv_slider_get_value(slider);
    
    
    LCD_PwmSetPulse(brightness);
	
	
		//保存到EEPROM里面
	
}
