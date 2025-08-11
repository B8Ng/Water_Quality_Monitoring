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




void setup_scr_DetailUI(lv_ui *ui)
{
    //Write codes DetailUI
    ui->DetailUI = lv_obj_create(NULL);
    lv_obj_set_size(ui->DetailUI, 480, 272);
    lv_obj_set_scrollbar_mode(ui->DetailUI, LV_SCROLLBAR_MODE_OFF);

    //Write style for DetailUI, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->DetailUI, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes DetailUI_title
    ui->DetailUI_title = lv_obj_create(ui->DetailUI);
    lv_obj_set_pos(ui->DetailUI_title, 0, 0);
    lv_obj_set_size(ui->DetailUI_title, 480, 50);
    lv_obj_set_scrollbar_mode(ui->DetailUI_title, LV_SCROLLBAR_MODE_OFF);

    //Write style for DetailUI_title, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->DetailUI_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->DetailUI_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->DetailUI_title, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->DetailUI_title, lv_color_hex(0x62b4e4), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->DetailUI_title, LV_GRAD_DIR_HOR, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui->DetailUI_title, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_main_stop(ui->DetailUI_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_stop(ui->DetailUI_title, 177, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->DetailUI_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->DetailUI_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->DetailUI_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->DetailUI_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->DetailUI_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes DetailUI_back
    ui->DetailUI_back = lv_btn_create(ui->DetailUI_title);
    ui->DetailUI_back_label = lv_label_create(ui->DetailUI_back);
    lv_label_set_text(ui->DetailUI_back_label, "Back");
    lv_label_set_long_mode(ui->DetailUI_back_label, LV_LABEL_LONG_SCROLL);
    lv_obj_align(ui->DetailUI_back_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->DetailUI_back, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->DetailUI_back_label, LV_PCT(100));
    lv_obj_set_pos(ui->DetailUI_back, 13, 6);
    lv_obj_set_size(ui->DetailUI_back, 87, 34);

    //Write style for DetailUI_back, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->DetailUI_back, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->DetailUI_back, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->DetailUI_back, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->DetailUI_back, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->DetailUI_back, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->DetailUI_back, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->DetailUI_back, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->DetailUI_back, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->DetailUI_back, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->DetailUI_back, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes DetailUI_th_setting
    ui->DetailUI_th_setting = lv_btn_create(ui->DetailUI_title);
    ui->DetailUI_th_setting_label = lv_label_create(ui->DetailUI_th_setting);
    lv_label_set_text(ui->DetailUI_th_setting_label, "Set");
    lv_label_set_long_mode(ui->DetailUI_th_setting_label, LV_LABEL_LONG_SCROLL);
    lv_obj_align(ui->DetailUI_th_setting_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->DetailUI_th_setting, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->DetailUI_th_setting_label, LV_PCT(100));
    lv_obj_set_pos(ui->DetailUI_th_setting, 380, 9);
    lv_obj_set_size(ui->DetailUI_th_setting, 87, 34);

    //Write style for DetailUI_th_setting, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->DetailUI_th_setting, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->DetailUI_th_setting, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->DetailUI_th_setting, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->DetailUI_th_setting, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->DetailUI_th_setting, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->DetailUI_th_setting, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->DetailUI_th_setting, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->DetailUI_th_setting, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->DetailUI_th_setting, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->DetailUI_th_setting, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes DetailUI_table
    ui->DetailUI_table = lv_obj_create(ui->DetailUI);
    lv_obj_set_pos(ui->DetailUI_table, 0, 50);
    lv_obj_set_size(ui->DetailUI_table, 480, 222);
    lv_obj_set_scrollbar_mode(ui->DetailUI_table, LV_SCROLLBAR_MODE_OFF);

    //Write style for DetailUI_table, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->DetailUI_table, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->DetailUI_table, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->DetailUI_table, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->DetailUI_table, lv_color_hex(0xf6f6f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->DetailUI_table, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->DetailUI_table, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->DetailUI_table, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->DetailUI_table, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->DetailUI_table, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->DetailUI_table, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes DetailUI_history
    ui->DetailUI_history = lv_chart_create(ui->DetailUI_table);
    lv_chart_set_type(ui->DetailUI_history, LV_CHART_TYPE_LINE);
    lv_chart_set_div_line_count(ui->DetailUI_history, 8, 6);
    lv_chart_set_point_count(ui->DetailUI_history, 6);
    lv_chart_set_range(ui->DetailUI_history, LV_CHART_AXIS_PRIMARY_Y, 0, 140);
    lv_chart_set_range(ui->DetailUI_history, LV_CHART_AXIS_SECONDARY_Y, 0, 2000);		//给TDS用
    lv_chart_set_zoom_x(ui->DetailUI_history, 256);
    lv_chart_set_zoom_y(ui->DetailUI_history, 256);
		
		
		//ph
    ui->DetailUI_history_0 = lv_chart_add_series(ui->DetailUI_history, lv_color_hex(0x4B0082), LV_CHART_AXIS_PRIMARY_Y);   // PH
		ui->DetailUI_history_1 = lv_chart_add_series(ui->DetailUI_history, lv_color_hex(0xFF7E00), LV_CHART_AXIS_SECONDARY_Y); // TDS
		ui->DetailUI_history_2 = lv_chart_add_series(ui->DetailUI_history, lv_color_hex(0xFF4500), LV_CHART_AXIS_PRIMARY_Y);    // 温度
		ui->DetailUI_history_3 = lv_chart_add_series(ui->DetailUI_history, lv_color_hex(0x778899), LV_CHART_AXIS_PRIMARY_Y); 		//ntu
		
    lv_obj_set_pos(ui->DetailUI_history, 254, 23);
    lv_obj_set_size(ui->DetailUI_history, 204, 181);
    lv_obj_set_scrollbar_mode(ui->DetailUI_history, LV_SCROLLBAR_MODE_OFF);

    //Write style for DetailUI_history, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->DetailUI_history, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->DetailUI_history, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->DetailUI_history, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->DetailUI_history, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->DetailUI_history, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->DetailUI_history, lv_color_hex(0xe8e8e8), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->DetailUI_history, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->DetailUI_history, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_width(ui->DetailUI_history, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui->DetailUI_history, lv_color_hex(0xe8e8e8), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui->DetailUI_history, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->DetailUI_history, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for DetailUI_history, Part: LV_PART_TICKS, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->DetailUI_history, lv_color_hex(0x151212), LV_PART_TICKS|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->DetailUI_history, &lv_font_montserratMedium_12, LV_PART_TICKS|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->DetailUI_history, 255, LV_PART_TICKS|LV_STATE_DEFAULT);
    lv_obj_set_style_line_width(ui->DetailUI_history, 2, LV_PART_TICKS|LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui->DetailUI_history, lv_color_hex(0xe8e8e8), LV_PART_TICKS|LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui->DetailUI_history, 255, LV_PART_TICKS|LV_STATE_DEFAULT);

    //Write codes DetailUI_node_detail
    ui->DetailUI_node_detail = lv_obj_create(ui->DetailUI_table);
    lv_obj_set_pos(ui->DetailUI_node_detail, 12, 9);
    lv_obj_set_size(ui->DetailUI_node_detail, 228, 196);
    lv_obj_set_scrollbar_mode(ui->DetailUI_node_detail, LV_SCROLLBAR_MODE_OFF);

    //Write style for DetailUI_node_detail, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->DetailUI_node_detail, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->DetailUI_node_detail, 12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->DetailUI_node_detail, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->DetailUI_node_detail, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->DetailUI_node_detail, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->DetailUI_node_detail, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->DetailUI_node_detail, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->DetailUI_node_detail, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->DetailUI_node_detail, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->DetailUI_node_detail, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes DetailUI_node_img
    ui->DetailUI_node_img = lv_img_create(ui->DetailUI_node_detail);
    lv_obj_add_flag(ui->DetailUI_node_img, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->DetailUI_node_img, &_nodeb_alpha_32x32);
    lv_img_set_pivot(ui->DetailUI_node_img, 50,50);
    lv_img_set_angle(ui->DetailUI_node_img, 0);
    lv_obj_set_pos(ui->DetailUI_node_img, 11, 10);
    lv_obj_set_size(ui->DetailUI_node_img, 32, 32);

    //Write style for DetailUI_node_img, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->DetailUI_node_img, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->DetailUI_node_img, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->DetailUI_node_img, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->DetailUI_node_img, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes DetailUI_node_num
    ui->DetailUI_node_num = lv_label_create(ui->DetailUI_node_detail);
    lv_label_set_text(ui->DetailUI_node_num, "Node 1");
    lv_label_set_long_mode(ui->DetailUI_node_num, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->DetailUI_node_num, 62, 18);
    lv_obj_set_size(ui->DetailUI_node_num, 98, 20);

    //Write style for DetailUI_node_num, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->DetailUI_node_num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->DetailUI_node_num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->DetailUI_node_num, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->DetailUI_node_num, &lv_font_montserratMedium_20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->DetailUI_node_num, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->DetailUI_node_num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->DetailUI_node_num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->DetailUI_node_num, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->DetailUI_node_num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->DetailUI_node_num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->DetailUI_node_num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->DetailUI_node_num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->DetailUI_node_num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->DetailUI_node_num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes DetailUI_battery
    ui->DetailUI_battery = lv_img_create(ui->DetailUI_node_detail);
    lv_obj_add_flag(ui->DetailUI_battery, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->DetailUI_battery, &_icon_dianchi_4_alpha_32x32);
    lv_img_set_pivot(ui->DetailUI_battery, 50,50);
    lv_img_set_angle(ui->DetailUI_battery, 0);
    lv_obj_set_pos(ui->DetailUI_battery, 163, 12);
    lv_obj_set_size(ui->DetailUI_battery, 32, 32);

    //Write style for DetailUI_battery, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->DetailUI_battery, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->DetailUI_battery, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->DetailUI_battery, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->DetailUI_battery, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes DetailUI_gps
    ui->DetailUI_gps = lv_label_create(ui->DetailUI_node_detail);
    lv_label_set_text(ui->DetailUI_gps, "GPS: NO SIGNAL");
    lv_label_set_long_mode(ui->DetailUI_gps, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->DetailUI_gps, 31, 62);
    lv_obj_set_size(ui->DetailUI_gps, 181, 19);

    //Write style for DetailUI_gps, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->DetailUI_gps, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->DetailUI_gps, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->DetailUI_gps, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->DetailUI_gps, &lv_font_montserratMedium_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->DetailUI_gps, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->DetailUI_gps, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->DetailUI_gps, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->DetailUI_gps, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->DetailUI_gps, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->DetailUI_gps, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->DetailUI_gps, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->DetailUI_gps, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->DetailUI_gps, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->DetailUI_gps, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes DetailUI_ph_label
    ui->DetailUI_ph_label = lv_label_create(ui->DetailUI_node_detail);
    lv_label_set_text(ui->DetailUI_ph_label, "PH: 0.0");
    lv_label_set_long_mode(ui->DetailUI_ph_label, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->DetailUI_ph_label, 32, 96);
    lv_obj_set_size(ui->DetailUI_ph_label, 72, 15);

    //Write style for DetailUI_ph_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->DetailUI_ph_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->DetailUI_ph_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->DetailUI_ph_label, lv_color_hex(0x4b0082), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->DetailUI_ph_label, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->DetailUI_ph_label, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->DetailUI_ph_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->DetailUI_ph_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->DetailUI_ph_label, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->DetailUI_ph_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->DetailUI_ph_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->DetailUI_ph_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->DetailUI_ph_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->DetailUI_ph_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->DetailUI_ph_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes DetailUI_tds
    ui->DetailUI_tds = lv_label_create(ui->DetailUI_node_detail);
    lv_label_set_text(ui->DetailUI_tds, "TDS:0");
    lv_label_set_long_mode(ui->DetailUI_tds, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->DetailUI_tds, 121, 95);
    lv_obj_set_size(ui->DetailUI_tds, 88, 15);

    //Write style for DetailUI_tds, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->DetailUI_tds, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->DetailUI_tds, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->DetailUI_tds, lv_color_hex(0xFF7E00), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->DetailUI_tds, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->DetailUI_tds, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->DetailUI_tds, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->DetailUI_tds, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->DetailUI_tds, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->DetailUI_tds, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->DetailUI_tds, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->DetailUI_tds, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->DetailUI_tds, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->DetailUI_tds, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->DetailUI_tds, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes DetailUI_temperature
    ui->DetailUI_temperature = lv_label_create(ui->DetailUI_node_detail);
    lv_label_set_text(ui->DetailUI_temperature, "T:0.0");
    lv_label_set_long_mode(ui->DetailUI_temperature, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->DetailUI_temperature, 43, 123);
    lv_obj_set_size(ui->DetailUI_temperature, 65, 14);

    //Write style for DetailUI_temperature, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->DetailUI_temperature, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->DetailUI_temperature, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->DetailUI_temperature, lv_color_hex(0xFF4500), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->DetailUI_temperature, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->DetailUI_temperature, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->DetailUI_temperature, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->DetailUI_temperature, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->DetailUI_temperature, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->DetailUI_temperature, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->DetailUI_temperature, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->DetailUI_temperature, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->DetailUI_temperature, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->DetailUI_temperature, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->DetailUI_temperature, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes DetailUI_ntu
    ui->DetailUI_ntu = lv_label_create(ui->DetailUI_node_detail);
    lv_label_set_text(ui->DetailUI_ntu, "NTU: 0.0");
    lv_label_set_long_mode(ui->DetailUI_ntu, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->DetailUI_ntu, 122, 124);
    lv_obj_set_size(ui->DetailUI_ntu, 88, 16);

    //Write style for DetailUI_ntu, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->DetailUI_ntu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->DetailUI_ntu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->DetailUI_ntu, lv_color_hex(0x778899), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->DetailUI_ntu, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->DetailUI_ntu, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->DetailUI_ntu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->DetailUI_ntu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->DetailUI_ntu, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->DetailUI_ntu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->DetailUI_ntu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->DetailUI_ntu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->DetailUI_ntu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->DetailUI_ntu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->DetailUI_ntu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes DetailUI_log
    ui->DetailUI_log = lv_btn_create(ui->DetailUI);
    ui->DetailUI_log_label = lv_label_create(ui->DetailUI_log);
    lv_label_set_text(ui->DetailUI_log_label, "Warning:0");
    lv_label_set_long_mode(ui->DetailUI_log_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->DetailUI_log_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->DetailUI_log, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->DetailUI_log_label, LV_PCT(100));
    lv_obj_set_pos(ui->DetailUI_log, 69, 210);
    lv_obj_set_size(ui->DetailUI_log, 104, 27);

    //Write style for DetailUI_log, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->DetailUI_log, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->DetailUI_log, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->DetailUI_log, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->DetailUI_log, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->DetailUI_log, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->DetailUI_log, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->DetailUI_log, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->DetailUI_log, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->DetailUI_log, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->DetailUI_log, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of DetailUI.
		//创建一个更新历史数据的计时器		5s刷新一次
		
		static bool DetailUI_history_timer_enabled = false;
    if (!DetailUI_history_timer_enabled) {
        lv_timer_create(SubData_history_timer, 5000, NULL);
        DetailUI_history_timer_enabled = true;
    }

    //Update current screen layout.
    lv_obj_update_layout(ui->DetailUI);

    //Init events for screen.
    events_init_DetailUI(ui);
}
