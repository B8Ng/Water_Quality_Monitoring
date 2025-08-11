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




void setup_scr_NodeUI(lv_ui *ui)
{
    //Write codes NodeUI
    ui->NodeUI = lv_obj_create(NULL);
    lv_obj_set_size(ui->NodeUI, 480, 272);
    lv_obj_set_scrollbar_mode(ui->NodeUI, LV_SCROLLBAR_MODE_OFF);

    //Write style for NodeUI, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->NodeUI, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes NodeUI_cont_1
    ui->NodeUI_cont_1 = lv_obj_create(ui->NodeUI);
    lv_obj_set_pos(ui->NodeUI_cont_1, 0, 0);
    lv_obj_set_size(ui->NodeUI_cont_1, 480, 50);
    lv_obj_set_scrollbar_mode(ui->NodeUI_cont_1, LV_SCROLLBAR_MODE_OFF);

    //Write style for NodeUI_cont_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->NodeUI_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->NodeUI_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->NodeUI_cont_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->NodeUI_cont_1, lv_color_hex(0x62b4e4), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->NodeUI_cont_1, LV_GRAD_DIR_HOR, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui->NodeUI_cont_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_main_stop(ui->NodeUI_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_stop(ui->NodeUI_cont_1, 177, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->NodeUI_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->NodeUI_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->NodeUI_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->NodeUI_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->NodeUI_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes NodeUI_back_button
    ui->NodeUI_back_button = lv_btn_create(ui->NodeUI_cont_1);
    ui->NodeUI_back_button_label = lv_label_create(ui->NodeUI_back_button);
    lv_label_set_text(ui->NodeUI_back_button_label, "Back");
    lv_label_set_long_mode(ui->NodeUI_back_button_label, LV_LABEL_LONG_SCROLL);
    lv_obj_align(ui->NodeUI_back_button_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->NodeUI_back_button, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->NodeUI_back_button_label, LV_PCT(100));
    lv_obj_set_pos(ui->NodeUI_back_button, 13, 6);
    lv_obj_set_size(ui->NodeUI_back_button, 87, 34);

    //Write style for NodeUI_back_button, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->NodeUI_back_button, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->NodeUI_back_button, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->NodeUI_back_button, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->NodeUI_back_button, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->NodeUI_back_button, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->NodeUI_back_button, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->NodeUI_back_button, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->NodeUI_back_button, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->NodeUI_back_button, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->NodeUI_back_button, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes NodeUI_table
    ui->NodeUI_table = lv_obj_create(ui->NodeUI);
    lv_obj_set_pos(ui->NodeUI_table, 0, 50);
    lv_obj_set_size(ui->NodeUI_table, 480, 222);
    lv_obj_set_scrollbar_mode(ui->NodeUI_table, LV_SCROLLBAR_MODE_AUTO);

    //Write style for NodeUI_table, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->NodeUI_table, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->NodeUI_table, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->NodeUI_table, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->NodeUI_table, lv_color_hex(0xf6f6f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->NodeUI_table, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->NodeUI_table, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->NodeUI_table, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->NodeUI_table, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->NodeUI_table, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->NodeUI_table, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes NodeUI_node_obj
    ui->NodeUI_node_obj = lv_obj_create(ui->NodeUI_table);
    lv_obj_set_pos(ui->NodeUI_node_obj, 12, 9);
    lv_obj_set_size(ui->NodeUI_node_obj, 451, 131);
    lv_obj_set_scrollbar_mode(ui->NodeUI_node_obj, LV_SCROLLBAR_MODE_OFF);

    //Write style for NodeUI_node_obj, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->NodeUI_node_obj, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->NodeUI_node_obj, 12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->NodeUI_node_obj, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->NodeUI_node_obj, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->NodeUI_node_obj, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->NodeUI_node_obj, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->NodeUI_node_obj, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->NodeUI_node_obj, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->NodeUI_node_obj, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->NodeUI_node_obj, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes NodeUI_node_img
    ui->NodeUI_node_img = lv_img_create(ui->NodeUI_node_obj);
    lv_obj_add_flag(ui->NodeUI_node_img, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->NodeUI_node_img, &_nodeb_alpha_32x32);
    lv_img_set_pivot(ui->NodeUI_node_img, 50,50);
    lv_img_set_angle(ui->NodeUI_node_img, 0);
    lv_obj_set_pos(ui->NodeUI_node_img, 22, 12);
    lv_obj_set_size(ui->NodeUI_node_img, 32, 32);

    //Write style for NodeUI_node_img, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->NodeUI_node_img, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->NodeUI_node_img, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->NodeUI_node_img, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->NodeUI_node_img, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes NodeUI_node_num
    ui->NodeUI_node_num = lv_label_create(ui->NodeUI_node_obj);
    lv_label_set_text(ui->NodeUI_node_num, "Node 1");
    lv_label_set_long_mode(ui->NodeUI_node_num, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->NodeUI_node_num, 72, 18);
    lv_obj_set_size(ui->NodeUI_node_num, 98, 20);

    //Write style for NodeUI_node_num, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->NodeUI_node_num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->NodeUI_node_num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->NodeUI_node_num, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->NodeUI_node_num, &lv_font_montserratMedium_20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->NodeUI_node_num, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->NodeUI_node_num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->NodeUI_node_num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->NodeUI_node_num, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->NodeUI_node_num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->NodeUI_node_num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->NodeUI_node_num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->NodeUI_node_num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->NodeUI_node_num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->NodeUI_node_num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes NodeUI_LoRaConnect
    ui->NodeUI_LoRaConnect = lv_label_create(ui->NodeUI_node_obj);
    lv_label_set_text(ui->NodeUI_LoRaConnect, "LoRa: Connect");
    lv_label_set_long_mode(ui->NodeUI_LoRaConnect, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->NodeUI_LoRaConnect, 173, 18);
    lv_obj_set_size(ui->NodeUI_LoRaConnect, 173, 30);

    //Write style for NodeUI_LoRaConnect, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->NodeUI_LoRaConnect, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->NodeUI_LoRaConnect, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->NodeUI_LoRaConnect, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->NodeUI_LoRaConnect, &lv_font_montserratMedium_21, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->NodeUI_LoRaConnect, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->NodeUI_LoRaConnect, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->NodeUI_LoRaConnect, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->NodeUI_LoRaConnect, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->NodeUI_LoRaConnect, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->NodeUI_LoRaConnect, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->NodeUI_LoRaConnect, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->NodeUI_LoRaConnect, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->NodeUI_LoRaConnect, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->NodeUI_LoRaConnect, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes NodeUI_battery
    ui->NodeUI_battery = lv_img_create(ui->NodeUI_node_obj);
    lv_obj_add_flag(ui->NodeUI_battery, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->NodeUI_battery, &_icon_dianchi_4_alpha_32x32);
    lv_img_set_pivot(ui->NodeUI_battery, 50,50);
    lv_img_set_angle(ui->NodeUI_battery, 0);
    lv_obj_set_pos(ui->NodeUI_battery, 384, 12);
    lv_obj_set_size(ui->NodeUI_battery, 32, 32);

    //Write style for NodeUI_battery, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->NodeUI_battery, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->NodeUI_battery, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->NodeUI_battery, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->NodeUI_battery, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes NodeUI_GPS
    ui->NodeUI_GPS = lv_label_create(ui->NodeUI_node_obj);
    lv_label_set_text(ui->NodeUI_GPS, "GPS: NO SIGNAL");
    lv_label_set_long_mode(ui->NodeUI_GPS, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->NodeUI_GPS, 73, 59);
    lv_obj_set_size(ui->NodeUI_GPS, 181, 19);

    //Write style for NodeUI_GPS, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->NodeUI_GPS, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->NodeUI_GPS, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->NodeUI_GPS, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->NodeUI_GPS, &lv_font_montserratMedium_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->NodeUI_GPS, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->NodeUI_GPS, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->NodeUI_GPS, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->NodeUI_GPS, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->NodeUI_GPS, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->NodeUI_GPS, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->NodeUI_GPS, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->NodeUI_GPS, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->NodeUI_GPS, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->NodeUI_GPS, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes NodeUI_log
    ui->NodeUI_log = lv_label_create(ui->NodeUI_node_obj);
    lv_label_set_text(ui->NodeUI_log, "Warning: 0");
    lv_label_set_long_mode(ui->NodeUI_log, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->NodeUI_log, 251, 61);
    lv_obj_set_size(ui->NodeUI_log, 156, 19);

    //Write style for NodeUI_log, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->NodeUI_log, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->NodeUI_log, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->NodeUI_log, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->NodeUI_log, &lv_font_montserratMedium_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->NodeUI_log, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->NodeUI_log, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->NodeUI_log, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->NodeUI_log, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->NodeUI_log, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->NodeUI_log, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->NodeUI_log, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->NodeUI_log, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->NodeUI_log, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->NodeUI_log, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes NodeUI_ph_label
    ui->NodeUI_ph_label = lv_label_create(ui->NodeUI_node_obj);
    lv_label_set_text(ui->NodeUI_ph_label, "PH: 0.0");
    lv_label_set_long_mode(ui->NodeUI_ph_label, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->NodeUI_ph_label, 74, 96);
    lv_obj_set_size(ui->NodeUI_ph_label, 72, 15);

    //Write style for NodeUI_ph_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->NodeUI_ph_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->NodeUI_ph_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->NodeUI_ph_label, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->NodeUI_ph_label, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->NodeUI_ph_label, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->NodeUI_ph_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->NodeUI_ph_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->NodeUI_ph_label, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->NodeUI_ph_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->NodeUI_ph_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->NodeUI_ph_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->NodeUI_ph_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->NodeUI_ph_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->NodeUI_ph_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes NodeUI_tds
    ui->NodeUI_tds = lv_label_create(ui->NodeUI_node_obj);
    lv_label_set_text(ui->NodeUI_tds, "TDS:0");
    lv_label_set_long_mode(ui->NodeUI_tds, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->NodeUI_tds, 154, 96);
    lv_obj_set_size(ui->NodeUI_tds, 88, 15);

    //Write style for NodeUI_tds, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->NodeUI_tds, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->NodeUI_tds, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->NodeUI_tds, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->NodeUI_tds, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->NodeUI_tds, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->NodeUI_tds, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->NodeUI_tds, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->NodeUI_tds, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->NodeUI_tds, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->NodeUI_tds, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->NodeUI_tds, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->NodeUI_tds, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->NodeUI_tds, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->NodeUI_tds, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes NodeUI_temperature
    ui->NodeUI_temperature = lv_label_create(ui->NodeUI_node_obj);
    lv_label_set_text(ui->NodeUI_temperature, "T:0");
    lv_label_set_long_mode(ui->NodeUI_temperature, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->NodeUI_temperature, 260, 97);
    lv_obj_set_size(ui->NodeUI_temperature, 65, 14);

    //Write style for NodeUI_temperature, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->NodeUI_temperature, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->NodeUI_temperature, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->NodeUI_temperature, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->NodeUI_temperature, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->NodeUI_temperature, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->NodeUI_temperature, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->NodeUI_temperature, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->NodeUI_temperature, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->NodeUI_temperature, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->NodeUI_temperature, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->NodeUI_temperature, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->NodeUI_temperature, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->NodeUI_temperature, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->NodeUI_temperature, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes NodeUI_dimness
    ui->NodeUI_dimness = lv_label_create(ui->NodeUI_node_obj);
    lv_label_set_text(ui->NodeUI_dimness, "NTU: 0.0");
    lv_label_set_long_mode(ui->NodeUI_dimness, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->NodeUI_dimness, 350, 96);
    lv_obj_set_size(ui->NodeUI_dimness, 88, 16);

    //Write style for NodeUI_dimness, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->NodeUI_dimness, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->NodeUI_dimness, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->NodeUI_dimness, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->NodeUI_dimness, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->NodeUI_dimness, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->NodeUI_dimness, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->NodeUI_dimness, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->NodeUI_dimness, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->NodeUI_dimness, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->NodeUI_dimness, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->NodeUI_dimness, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->NodeUI_dimness, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->NodeUI_dimness, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->NodeUI_dimness, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of NodeUI.
		static bool NodeUI_Update_timer_enabled = false;
    if (!NodeUI_Update_timer_enabled) {
        lv_timer_create(SubData_timer , 1000, NULL);			//创建一个更新NodeUI的定时器
        NodeUI_Update_timer_enabled = true;
    }

    //Update current screen layout.
    lv_obj_update_layout(ui->NodeUI);

    //Init events for screen.
    events_init_NodeUI(ui);
}
