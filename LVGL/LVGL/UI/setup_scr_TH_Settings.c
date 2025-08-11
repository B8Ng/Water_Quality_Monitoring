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
#include "DX511.h"

extern SensorSettingData SettingData;

void setup_scr_TH_Settings(lv_ui *ui)
{
    //Write codes TH_Settings
    ui->TH_Settings = lv_obj_create(NULL);
    lv_obj_set_size(ui->TH_Settings, 480, 272);
    lv_obj_set_scrollbar_mode(ui->TH_Settings, LV_SCROLLBAR_MODE_OFF);

    //Write style for TH_Settings, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->TH_Settings, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes TH_Settings_cont_1
    ui->TH_Settings_cont_1 = lv_obj_create(ui->TH_Settings);
    lv_obj_set_pos(ui->TH_Settings_cont_1, 0, 0);
    lv_obj_set_size(ui->TH_Settings_cont_1, 480, 50);
    lv_obj_set_scrollbar_mode(ui->TH_Settings_cont_1, LV_SCROLLBAR_MODE_OFF);

    //Write style for TH_Settings_cont_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->TH_Settings_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->TH_Settings_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->TH_Settings_cont_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->TH_Settings_cont_1, lv_color_hex(0x62b4e4), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->TH_Settings_cont_1, LV_GRAD_DIR_HOR, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui->TH_Settings_cont_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_main_stop(ui->TH_Settings_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_stop(ui->TH_Settings_cont_1, 177, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->TH_Settings_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->TH_Settings_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->TH_Settings_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->TH_Settings_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->TH_Settings_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes TH_Settings_back
    ui->TH_Settings_back = lv_btn_create(ui->TH_Settings_cont_1);
    ui->TH_Settings_back_label = lv_label_create(ui->TH_Settings_back);
    lv_label_set_text(ui->TH_Settings_back_label, "Back");
    lv_label_set_long_mode(ui->TH_Settings_back_label, LV_LABEL_LONG_SCROLL);
    lv_obj_align(ui->TH_Settings_back_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->TH_Settings_back, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->TH_Settings_back_label, LV_PCT(100));
    lv_obj_set_pos(ui->TH_Settings_back, 13, 6);
    lv_obj_set_size(ui->TH_Settings_back, 87, 34);

    //Write style for TH_Settings_back, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->TH_Settings_back, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->TH_Settings_back, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->TH_Settings_back, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->TH_Settings_back, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->TH_Settings_back, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->TH_Settings_back, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->TH_Settings_back, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->TH_Settings_back, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->TH_Settings_back, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->TH_Settings_back, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes TH_Settings_save
    ui->TH_Settings_save = lv_btn_create(ui->TH_Settings_cont_1);
    ui->TH_Settings_save_label = lv_label_create(ui->TH_Settings_save);
    lv_label_set_text(ui->TH_Settings_save_label, "Save");
    lv_label_set_long_mode(ui->TH_Settings_save_label, LV_LABEL_LONG_SCROLL);
    lv_obj_align(ui->TH_Settings_save_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->TH_Settings_save, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->TH_Settings_save_label, LV_PCT(100));
    lv_obj_set_pos(ui->TH_Settings_save, 381, 8);
    lv_obj_set_size(ui->TH_Settings_save, 87, 34);

    //Write style for TH_Settings_save, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->TH_Settings_save, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->TH_Settings_save, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->TH_Settings_save, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->TH_Settings_save, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->TH_Settings_save, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->TH_Settings_save, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->TH_Settings_save, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->TH_Settings_save, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->TH_Settings_save, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->TH_Settings_save, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes TH_Settings_Setting
    ui->TH_Settings_Setting = lv_obj_create(ui->TH_Settings);
    lv_obj_set_pos(ui->TH_Settings_Setting, 0, 50);
    lv_obj_set_size(ui->TH_Settings_Setting, 480, 222);
    lv_obj_set_scrollbar_mode(ui->TH_Settings_Setting, LV_SCROLLBAR_MODE_AUTO);

    //Write style for TH_Settings_Setting, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->TH_Settings_Setting, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->TH_Settings_Setting, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->TH_Settings_Setting, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->TH_Settings_Setting, lv_color_hex(0xf6f6f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->TH_Settings_Setting, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->TH_Settings_Setting, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->TH_Settings_Setting, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->TH_Settings_Setting, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->TH_Settings_Setting, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->TH_Settings_Setting, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes TH_Settings_ph_label
    ui->TH_Settings_ph_label = lv_obj_create(ui->TH_Settings_Setting);
    lv_obj_set_pos(ui->TH_Settings_ph_label, 7, 10);
    lv_obj_set_size(ui->TH_Settings_ph_label, 465, 50);
    lv_obj_set_scrollbar_mode(ui->TH_Settings_ph_label, LV_SCROLLBAR_MODE_OFF);

    //Write style for TH_Settings_ph_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->TH_Settings_ph_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->TH_Settings_ph_label, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->TH_Settings_ph_label, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->TH_Settings_ph_label, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->TH_Settings_ph_label, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->TH_Settings_ph_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->TH_Settings_ph_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->TH_Settings_ph_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->TH_Settings_ph_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->TH_Settings_ph_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes TH_Settings_high
    ui->TH_Settings_high = lv_label_create(ui->TH_Settings_ph_label);
    lv_label_set_text(ui->TH_Settings_high, "H:");
    lv_label_set_long_mode(ui->TH_Settings_high, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->TH_Settings_high, 347, 17);
    lv_obj_set_size(ui->TH_Settings_high, 30, 25);

    //Write style for TH_Settings_high, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->TH_Settings_high, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->TH_Settings_high, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->TH_Settings_high, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->TH_Settings_high, &lv_font_montserratMedium_21, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->TH_Settings_high, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->TH_Settings_high, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->TH_Settings_high, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->TH_Settings_high, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->TH_Settings_high, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->TH_Settings_high, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->TH_Settings_high, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->TH_Settings_high, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->TH_Settings_high, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->TH_Settings_high, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes TH_Settings_lowlist
    ui->TH_Settings_lowlist = lv_dropdown_create(ui->TH_Settings_ph_label);
    lv_dropdown_set_options(ui->TH_Settings_lowlist, "0\n1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n11\n12\n13\n14");
		//lv_dropdown_set_selected(ui->TH_Settings_lowlist, 3);
    lv_obj_set_pos(ui->TH_Settings_lowlist, 281, 15);
    lv_obj_set_size(ui->TH_Settings_lowlist, 50, 25);

    //Write style for TH_Settings_lowlist, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->TH_Settings_lowlist, lv_color_hex(0x0D3055), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->TH_Settings_lowlist, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->TH_Settings_lowlist, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->TH_Settings_lowlist, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->TH_Settings_lowlist, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->TH_Settings_lowlist, lv_color_hex(0xe1e6ee), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->TH_Settings_lowlist, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->TH_Settings_lowlist, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->TH_Settings_lowlist, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->TH_Settings_lowlist, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->TH_Settings_lowlist, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->TH_Settings_lowlist, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->TH_Settings_lowlist, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->TH_Settings_lowlist, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->TH_Settings_lowlist, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_CHECKED for &style_TH_Settings_lowlist_extra_list_selected_checked
    static lv_style_t style_TH_Settings_lowlist_extra_list_selected_checked;
    ui_init_style(&style_TH_Settings_lowlist_extra_list_selected_checked);

    lv_style_set_border_width(&style_TH_Settings_lowlist_extra_list_selected_checked, 1);
    lv_style_set_border_opa(&style_TH_Settings_lowlist_extra_list_selected_checked, 255);
    lv_style_set_border_color(&style_TH_Settings_lowlist_extra_list_selected_checked, lv_color_hex(0xe1e6ee));
    lv_style_set_border_side(&style_TH_Settings_lowlist_extra_list_selected_checked, LV_BORDER_SIDE_FULL);
    lv_style_set_radius(&style_TH_Settings_lowlist_extra_list_selected_checked, 3);
    lv_style_set_bg_opa(&style_TH_Settings_lowlist_extra_list_selected_checked, 255);
    lv_style_set_bg_color(&style_TH_Settings_lowlist_extra_list_selected_checked, lv_color_hex(0x00a1b5));
    lv_style_set_bg_grad_dir(&style_TH_Settings_lowlist_extra_list_selected_checked, LV_GRAD_DIR_NONE);
    lv_obj_add_style(lv_dropdown_get_list(ui->TH_Settings_lowlist), &style_TH_Settings_lowlist_extra_list_selected_checked, LV_PART_SELECTED|LV_STATE_CHECKED);

    //Write style state: LV_STATE_DEFAULT for &style_TH_Settings_lowlist_extra_list_main_default
    static lv_style_t style_TH_Settings_lowlist_extra_list_main_default;
    ui_init_style(&style_TH_Settings_lowlist_extra_list_main_default);

    lv_style_set_max_height(&style_TH_Settings_lowlist_extra_list_main_default, 90);
    lv_style_set_text_color(&style_TH_Settings_lowlist_extra_list_main_default, lv_color_hex(0x0D3055));
    lv_style_set_text_font(&style_TH_Settings_lowlist_extra_list_main_default, &lv_font_montserratMedium_12);
    lv_style_set_text_opa(&style_TH_Settings_lowlist_extra_list_main_default, 255);
    lv_style_set_border_width(&style_TH_Settings_lowlist_extra_list_main_default, 1);
    lv_style_set_border_opa(&style_TH_Settings_lowlist_extra_list_main_default, 255);
    lv_style_set_border_color(&style_TH_Settings_lowlist_extra_list_main_default, lv_color_hex(0xe1e6ee));
    lv_style_set_border_side(&style_TH_Settings_lowlist_extra_list_main_default, LV_BORDER_SIDE_FULL);
    lv_style_set_radius(&style_TH_Settings_lowlist_extra_list_main_default, 3);
    lv_style_set_bg_opa(&style_TH_Settings_lowlist_extra_list_main_default, 255);
    lv_style_set_bg_color(&style_TH_Settings_lowlist_extra_list_main_default, lv_color_hex(0xffffff));
    lv_style_set_bg_grad_dir(&style_TH_Settings_lowlist_extra_list_main_default, LV_GRAD_DIR_NONE);
    lv_obj_add_style(lv_dropdown_get_list(ui->TH_Settings_lowlist), &style_TH_Settings_lowlist_extra_list_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_TH_Settings_lowlist_extra_list_scrollbar_default
    static lv_style_t style_TH_Settings_lowlist_extra_list_scrollbar_default;
    ui_init_style(&style_TH_Settings_lowlist_extra_list_scrollbar_default);

    lv_style_set_radius(&style_TH_Settings_lowlist_extra_list_scrollbar_default, 3);
    lv_style_set_bg_opa(&style_TH_Settings_lowlist_extra_list_scrollbar_default, 255);
    lv_style_set_bg_color(&style_TH_Settings_lowlist_extra_list_scrollbar_default, lv_color_hex(0x00ff00));
    lv_style_set_bg_grad_dir(&style_TH_Settings_lowlist_extra_list_scrollbar_default, LV_GRAD_DIR_NONE);
    lv_obj_add_style(lv_dropdown_get_list(ui->TH_Settings_lowlist), &style_TH_Settings_lowlist_extra_list_scrollbar_default, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

    //Write codes TH_Settings_high_list
    ui->TH_Settings_high_list = lv_dropdown_create(ui->TH_Settings_ph_label);
    lv_dropdown_set_options(ui->TH_Settings_high_list, "0\n1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n11\n12\n13\n14");
		//lv_dropdown_set_selected(ui->TH_Settings_high_list,10);
    lv_obj_set_pos(ui->TH_Settings_high_list, 386, 15);
    lv_obj_set_size(ui->TH_Settings_high_list, 50, 25);

    //Write style for TH_Settings_high_list, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->TH_Settings_high_list, lv_color_hex(0x0D3055), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->TH_Settings_high_list, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->TH_Settings_high_list, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->TH_Settings_high_list, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->TH_Settings_high_list, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->TH_Settings_high_list, lv_color_hex(0xe1e6ee), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->TH_Settings_high_list, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->TH_Settings_high_list, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->TH_Settings_high_list, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->TH_Settings_high_list, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->TH_Settings_high_list, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->TH_Settings_high_list, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->TH_Settings_high_list, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->TH_Settings_high_list, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->TH_Settings_high_list, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_CHECKED for &style_TH_Settings_high_list_extra_list_selected_checked
    static lv_style_t style_TH_Settings_high_list_extra_list_selected_checked;
    ui_init_style(&style_TH_Settings_high_list_extra_list_selected_checked);

    lv_style_set_border_width(&style_TH_Settings_high_list_extra_list_selected_checked, 1);
    lv_style_set_border_opa(&style_TH_Settings_high_list_extra_list_selected_checked, 255);
    lv_style_set_border_color(&style_TH_Settings_high_list_extra_list_selected_checked, lv_color_hex(0xe1e6ee));
    lv_style_set_border_side(&style_TH_Settings_high_list_extra_list_selected_checked, LV_BORDER_SIDE_FULL);
    lv_style_set_radius(&style_TH_Settings_high_list_extra_list_selected_checked, 3);
    lv_style_set_bg_opa(&style_TH_Settings_high_list_extra_list_selected_checked, 255);
    lv_style_set_bg_color(&style_TH_Settings_high_list_extra_list_selected_checked, lv_color_hex(0x00a1b5));
    lv_style_set_bg_grad_dir(&style_TH_Settings_high_list_extra_list_selected_checked, LV_GRAD_DIR_NONE);
    lv_obj_add_style(lv_dropdown_get_list(ui->TH_Settings_high_list), &style_TH_Settings_high_list_extra_list_selected_checked, LV_PART_SELECTED|LV_STATE_CHECKED);

    //Write style state: LV_STATE_DEFAULT for &style_TH_Settings_high_list_extra_list_main_default
    static lv_style_t style_TH_Settings_high_list_extra_list_main_default;
    ui_init_style(&style_TH_Settings_high_list_extra_list_main_default);

    lv_style_set_max_height(&style_TH_Settings_high_list_extra_list_main_default, 90);
    lv_style_set_text_color(&style_TH_Settings_high_list_extra_list_main_default, lv_color_hex(0x0D3055));
    lv_style_set_text_font(&style_TH_Settings_high_list_extra_list_main_default, &lv_font_montserratMedium_12);
    lv_style_set_text_opa(&style_TH_Settings_high_list_extra_list_main_default, 255);
    lv_style_set_border_width(&style_TH_Settings_high_list_extra_list_main_default, 1);
    lv_style_set_border_opa(&style_TH_Settings_high_list_extra_list_main_default, 255);
    lv_style_set_border_color(&style_TH_Settings_high_list_extra_list_main_default, lv_color_hex(0xe1e6ee));
    lv_style_set_border_side(&style_TH_Settings_high_list_extra_list_main_default, LV_BORDER_SIDE_FULL);
    lv_style_set_radius(&style_TH_Settings_high_list_extra_list_main_default, 3);
    lv_style_set_bg_opa(&style_TH_Settings_high_list_extra_list_main_default, 255);
    lv_style_set_bg_color(&style_TH_Settings_high_list_extra_list_main_default, lv_color_hex(0xffffff));
    lv_style_set_bg_grad_dir(&style_TH_Settings_high_list_extra_list_main_default, LV_GRAD_DIR_NONE);
    lv_obj_add_style(lv_dropdown_get_list(ui->TH_Settings_high_list), &style_TH_Settings_high_list_extra_list_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_TH_Settings_high_list_extra_list_scrollbar_default
    static lv_style_t style_TH_Settings_high_list_extra_list_scrollbar_default;
    ui_init_style(&style_TH_Settings_high_list_extra_list_scrollbar_default);

    lv_style_set_radius(&style_TH_Settings_high_list_extra_list_scrollbar_default, 3);
    lv_style_set_bg_opa(&style_TH_Settings_high_list_extra_list_scrollbar_default, 255);
    lv_style_set_bg_color(&style_TH_Settings_high_list_extra_list_scrollbar_default, lv_color_hex(0x00ff00));
    lv_style_set_bg_grad_dir(&style_TH_Settings_high_list_extra_list_scrollbar_default, LV_GRAD_DIR_NONE);
    lv_obj_add_style(lv_dropdown_get_list(ui->TH_Settings_high_list), &style_TH_Settings_high_list_extra_list_scrollbar_default, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

    //Write codes TH_Settings_ph_l
    ui->TH_Settings_ph_l = lv_label_create(ui->TH_Settings_ph_label);
    lv_label_set_text(ui->TH_Settings_ph_l, "pH\n");
    lv_label_set_long_mode(ui->TH_Settings_ph_l, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->TH_Settings_ph_l, 7, 14);
    lv_obj_set_size(ui->TH_Settings_ph_l, 100, 27);

    //Write style for TH_Settings_ph_l, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->TH_Settings_ph_l, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->TH_Settings_ph_l, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->TH_Settings_ph_l, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->TH_Settings_ph_l, &lv_font_montserratMedium_21, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->TH_Settings_ph_l, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->TH_Settings_ph_l, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->TH_Settings_ph_l, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->TH_Settings_ph_l, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->TH_Settings_ph_l, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->TH_Settings_ph_l, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->TH_Settings_ph_l, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->TH_Settings_ph_l, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->TH_Settings_ph_l, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->TH_Settings_ph_l, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes TH_Settings_low
    ui->TH_Settings_low = lv_label_create(ui->TH_Settings_ph_label);
    lv_label_set_text(ui->TH_Settings_low, "L:\n");
    lv_label_set_long_mode(ui->TH_Settings_low, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->TH_Settings_low, 237, 16);
    lv_obj_set_size(ui->TH_Settings_low, 38, 24);

    //Write style for TH_Settings_low, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->TH_Settings_low, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->TH_Settings_low, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->TH_Settings_low, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->TH_Settings_low, &lv_font_montserratMedium_21, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->TH_Settings_low, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->TH_Settings_low, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->TH_Settings_low, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->TH_Settings_low, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->TH_Settings_low, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->TH_Settings_low, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->TH_Settings_low, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->TH_Settings_low, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->TH_Settings_low, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->TH_Settings_low, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes TH_Settings_TDS
    ui->TH_Settings_TDS = lv_obj_create(ui->TH_Settings_Setting);
    lv_obj_set_pos(ui->TH_Settings_TDS, 6, 68);
    lv_obj_set_size(ui->TH_Settings_TDS, 465, 48);
    lv_obj_set_scrollbar_mode(ui->TH_Settings_TDS, LV_SCROLLBAR_MODE_OFF);

    //Write style for TH_Settings_TDS, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->TH_Settings_TDS, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->TH_Settings_TDS, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->TH_Settings_TDS, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->TH_Settings_TDS, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->TH_Settings_TDS, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->TH_Settings_TDS, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->TH_Settings_TDS, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->TH_Settings_TDS, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->TH_Settings_TDS, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->TH_Settings_TDS, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes TH_Settings_highlist_2
    ui->TH_Settings_highlist_2 = lv_dropdown_create(ui->TH_Settings_TDS);
    lv_dropdown_set_options(ui->TH_Settings_highlist_2, "100\n200\n300\n400\n500\n600\n700\n800\n900\n1000");
		//lv_dropdown_set_selected(ui->TH_Settings_highlist_2,9);			//默认是1000
    lv_obj_set_pos(ui->TH_Settings_highlist_2, 384, 12);
    lv_obj_set_size(ui->TH_Settings_highlist_2, 52, 25);

    //Write style for TH_Settings_highlist_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->TH_Settings_highlist_2, lv_color_hex(0x0D3055), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->TH_Settings_highlist_2, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->TH_Settings_highlist_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->TH_Settings_highlist_2, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->TH_Settings_highlist_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->TH_Settings_highlist_2, lv_color_hex(0xe1e6ee), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->TH_Settings_highlist_2, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->TH_Settings_highlist_2, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->TH_Settings_highlist_2, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->TH_Settings_highlist_2, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->TH_Settings_highlist_2, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->TH_Settings_highlist_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->TH_Settings_highlist_2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->TH_Settings_highlist_2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->TH_Settings_highlist_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_CHECKED for &style_TH_Settings_highlist_2_extra_list_selected_checked
    static lv_style_t style_TH_Settings_highlist_2_extra_list_selected_checked;
    ui_init_style(&style_TH_Settings_highlist_2_extra_list_selected_checked);

    lv_style_set_border_width(&style_TH_Settings_highlist_2_extra_list_selected_checked, 1);
    lv_style_set_border_opa(&style_TH_Settings_highlist_2_extra_list_selected_checked, 255);
    lv_style_set_border_color(&style_TH_Settings_highlist_2_extra_list_selected_checked, lv_color_hex(0xe1e6ee));
    lv_style_set_border_side(&style_TH_Settings_highlist_2_extra_list_selected_checked, LV_BORDER_SIDE_FULL);
    lv_style_set_radius(&style_TH_Settings_highlist_2_extra_list_selected_checked, 3);
    lv_style_set_bg_opa(&style_TH_Settings_highlist_2_extra_list_selected_checked, 255);
    lv_style_set_bg_color(&style_TH_Settings_highlist_2_extra_list_selected_checked, lv_color_hex(0x00a1b5));
    lv_style_set_bg_grad_dir(&style_TH_Settings_highlist_2_extra_list_selected_checked, LV_GRAD_DIR_NONE);
    lv_obj_add_style(lv_dropdown_get_list(ui->TH_Settings_highlist_2), &style_TH_Settings_highlist_2_extra_list_selected_checked, LV_PART_SELECTED|LV_STATE_CHECKED);

    //Write style state: LV_STATE_DEFAULT for &style_TH_Settings_highlist_2_extra_list_main_default
    static lv_style_t style_TH_Settings_highlist_2_extra_list_main_default;
    ui_init_style(&style_TH_Settings_highlist_2_extra_list_main_default);

    lv_style_set_max_height(&style_TH_Settings_highlist_2_extra_list_main_default, 90);
    lv_style_set_text_color(&style_TH_Settings_highlist_2_extra_list_main_default, lv_color_hex(0x0D3055));
    lv_style_set_text_font(&style_TH_Settings_highlist_2_extra_list_main_default, &lv_font_montserratMedium_12);
    lv_style_set_text_opa(&style_TH_Settings_highlist_2_extra_list_main_default, 255);
    lv_style_set_border_width(&style_TH_Settings_highlist_2_extra_list_main_default, 1);
    lv_style_set_border_opa(&style_TH_Settings_highlist_2_extra_list_main_default, 255);
    lv_style_set_border_color(&style_TH_Settings_highlist_2_extra_list_main_default, lv_color_hex(0xe1e6ee));
    lv_style_set_border_side(&style_TH_Settings_highlist_2_extra_list_main_default, LV_BORDER_SIDE_FULL);
    lv_style_set_radius(&style_TH_Settings_highlist_2_extra_list_main_default, 3);
    lv_style_set_bg_opa(&style_TH_Settings_highlist_2_extra_list_main_default, 255);
    lv_style_set_bg_color(&style_TH_Settings_highlist_2_extra_list_main_default, lv_color_hex(0xffffff));
    lv_style_set_bg_grad_dir(&style_TH_Settings_highlist_2_extra_list_main_default, LV_GRAD_DIR_NONE);
    lv_obj_add_style(lv_dropdown_get_list(ui->TH_Settings_highlist_2), &style_TH_Settings_highlist_2_extra_list_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_TH_Settings_highlist_2_extra_list_scrollbar_default
    static lv_style_t style_TH_Settings_highlist_2_extra_list_scrollbar_default;
    ui_init_style(&style_TH_Settings_highlist_2_extra_list_scrollbar_default);

    lv_style_set_radius(&style_TH_Settings_highlist_2_extra_list_scrollbar_default, 3);
    lv_style_set_bg_opa(&style_TH_Settings_highlist_2_extra_list_scrollbar_default, 255);
    lv_style_set_bg_color(&style_TH_Settings_highlist_2_extra_list_scrollbar_default, lv_color_hex(0x00ff00));
    lv_style_set_bg_grad_dir(&style_TH_Settings_highlist_2_extra_list_scrollbar_default, LV_GRAD_DIR_NONE);
    lv_obj_add_style(lv_dropdown_get_list(ui->TH_Settings_highlist_2), &style_TH_Settings_highlist_2_extra_list_scrollbar_default, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

    //Write codes TH_Settings_tds
    ui->TH_Settings_tds = lv_label_create(ui->TH_Settings_TDS);
    lv_label_set_text(ui->TH_Settings_tds, "TDS\n");
    lv_label_set_long_mode(ui->TH_Settings_tds, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->TH_Settings_tds, 9, 14);
    lv_obj_set_size(ui->TH_Settings_tds, 100, 27);

    //Write style for TH_Settings_tds, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->TH_Settings_tds, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->TH_Settings_tds, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->TH_Settings_tds, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->TH_Settings_tds, &lv_font_montserratMedium_21, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->TH_Settings_tds, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->TH_Settings_tds, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->TH_Settings_tds, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->TH_Settings_tds, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->TH_Settings_tds, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->TH_Settings_tds, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->TH_Settings_tds, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->TH_Settings_tds, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->TH_Settings_tds, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->TH_Settings_tds, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes TH_Settings_T_lable
    ui->TH_Settings_T_lable = lv_obj_create(ui->TH_Settings_Setting);
    lv_obj_set_pos(ui->TH_Settings_T_lable, 7, 125);
    lv_obj_set_size(ui->TH_Settings_T_lable, 465, 48);
    lv_obj_set_scrollbar_mode(ui->TH_Settings_T_lable, LV_SCROLLBAR_MODE_OFF);

    //Write style for TH_Settings_T_lable, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->TH_Settings_T_lable, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->TH_Settings_T_lable, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->TH_Settings_T_lable, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->TH_Settings_T_lable, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->TH_Settings_T_lable, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->TH_Settings_T_lable, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->TH_Settings_T_lable, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->TH_Settings_T_lable, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->TH_Settings_T_lable, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->TH_Settings_T_lable, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes TH_Settings_highlabel_3
    ui->TH_Settings_highlabel_3 = lv_label_create(ui->TH_Settings_T_lable);
    lv_label_set_text(ui->TH_Settings_highlabel_3, "H:");
    lv_label_set_long_mode(ui->TH_Settings_highlabel_3, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->TH_Settings_highlabel_3, 347, 17);
    lv_obj_set_size(ui->TH_Settings_highlabel_3, 30, 25);

    //Write style for TH_Settings_highlabel_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->TH_Settings_highlabel_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->TH_Settings_highlabel_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->TH_Settings_highlabel_3, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->TH_Settings_highlabel_3, &lv_font_montserratMedium_21, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->TH_Settings_highlabel_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->TH_Settings_highlabel_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->TH_Settings_highlabel_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->TH_Settings_highlabel_3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->TH_Settings_highlabel_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->TH_Settings_highlabel_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->TH_Settings_highlabel_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->TH_Settings_highlabel_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->TH_Settings_highlabel_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->TH_Settings_highlabel_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes TH_Settings_lowddlist_3
    ui->TH_Settings_lowddlist_3 = lv_dropdown_create(ui->TH_Settings_T_lable);
    lv_dropdown_set_options(ui->TH_Settings_lowddlist_3, "-20\n-15\n-10\n-5\n0\n5\n10\n15\n20\n25\n30\n40\n50\n60");//设置温度阈值
		//lv_dropdown_set_selected(ui->TH_Settings_lowddlist_3, 4);
    lv_obj_set_pos(ui->TH_Settings_lowddlist_3, 281, 15);
    lv_obj_set_size(ui->TH_Settings_lowddlist_3, 52, 25);

    //Write style for TH_Settings_lowddlist_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->TH_Settings_lowddlist_3, lv_color_hex(0x0D3055), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->TH_Settings_lowddlist_3, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->TH_Settings_lowddlist_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->TH_Settings_lowddlist_3, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->TH_Settings_lowddlist_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->TH_Settings_lowddlist_3, lv_color_hex(0xe1e6ee), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->TH_Settings_lowddlist_3, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->TH_Settings_lowddlist_3, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->TH_Settings_lowddlist_3, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->TH_Settings_lowddlist_3, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->TH_Settings_lowddlist_3, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->TH_Settings_lowddlist_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->TH_Settings_lowddlist_3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->TH_Settings_lowddlist_3, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->TH_Settings_lowddlist_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_CHECKED for &style_TH_Settings_lowddlist_3_extra_list_selected_checked
    static lv_style_t style_TH_Settings_lowddlist_3_extra_list_selected_checked;
    ui_init_style(&style_TH_Settings_lowddlist_3_extra_list_selected_checked);

    lv_style_set_border_width(&style_TH_Settings_lowddlist_3_extra_list_selected_checked, 1);
    lv_style_set_border_opa(&style_TH_Settings_lowddlist_3_extra_list_selected_checked, 255);
    lv_style_set_border_color(&style_TH_Settings_lowddlist_3_extra_list_selected_checked, lv_color_hex(0xe1e6ee));
    lv_style_set_border_side(&style_TH_Settings_lowddlist_3_extra_list_selected_checked, LV_BORDER_SIDE_FULL);
    lv_style_set_radius(&style_TH_Settings_lowddlist_3_extra_list_selected_checked, 3);
    lv_style_set_bg_opa(&style_TH_Settings_lowddlist_3_extra_list_selected_checked, 255);
    lv_style_set_bg_color(&style_TH_Settings_lowddlist_3_extra_list_selected_checked, lv_color_hex(0x00a1b5));
    lv_style_set_bg_grad_dir(&style_TH_Settings_lowddlist_3_extra_list_selected_checked, LV_GRAD_DIR_NONE);
    lv_obj_add_style(lv_dropdown_get_list(ui->TH_Settings_lowddlist_3), &style_TH_Settings_lowddlist_3_extra_list_selected_checked, LV_PART_SELECTED|LV_STATE_CHECKED);

    //Write style state: LV_STATE_DEFAULT for &style_TH_Settings_lowddlist_3_extra_list_main_default
    static lv_style_t style_TH_Settings_lowddlist_3_extra_list_main_default;
    ui_init_style(&style_TH_Settings_lowddlist_3_extra_list_main_default);

    lv_style_set_max_height(&style_TH_Settings_lowddlist_3_extra_list_main_default, 90);
    lv_style_set_text_color(&style_TH_Settings_lowddlist_3_extra_list_main_default, lv_color_hex(0x0D3055));
    lv_style_set_text_font(&style_TH_Settings_lowddlist_3_extra_list_main_default, &lv_font_montserratMedium_12);
    lv_style_set_text_opa(&style_TH_Settings_lowddlist_3_extra_list_main_default, 255);
    lv_style_set_border_width(&style_TH_Settings_lowddlist_3_extra_list_main_default, 1);
    lv_style_set_border_opa(&style_TH_Settings_lowddlist_3_extra_list_main_default, 255);
    lv_style_set_border_color(&style_TH_Settings_lowddlist_3_extra_list_main_default, lv_color_hex(0xe1e6ee));
    lv_style_set_border_side(&style_TH_Settings_lowddlist_3_extra_list_main_default, LV_BORDER_SIDE_FULL);
    lv_style_set_radius(&style_TH_Settings_lowddlist_3_extra_list_main_default, 3);
    lv_style_set_bg_opa(&style_TH_Settings_lowddlist_3_extra_list_main_default, 255);
    lv_style_set_bg_color(&style_TH_Settings_lowddlist_3_extra_list_main_default, lv_color_hex(0xffffff));
    lv_style_set_bg_grad_dir(&style_TH_Settings_lowddlist_3_extra_list_main_default, LV_GRAD_DIR_NONE);
    lv_obj_add_style(lv_dropdown_get_list(ui->TH_Settings_lowddlist_3), &style_TH_Settings_lowddlist_3_extra_list_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_TH_Settings_lowddlist_3_extra_list_scrollbar_default
    static lv_style_t style_TH_Settings_lowddlist_3_extra_list_scrollbar_default;
    ui_init_style(&style_TH_Settings_lowddlist_3_extra_list_scrollbar_default);

    lv_style_set_radius(&style_TH_Settings_lowddlist_3_extra_list_scrollbar_default, 3);
    lv_style_set_bg_opa(&style_TH_Settings_lowddlist_3_extra_list_scrollbar_default, 255);
    lv_style_set_bg_color(&style_TH_Settings_lowddlist_3_extra_list_scrollbar_default, lv_color_hex(0x00ff00));
    lv_style_set_bg_grad_dir(&style_TH_Settings_lowddlist_3_extra_list_scrollbar_default, LV_GRAD_DIR_NONE);
    lv_obj_add_style(lv_dropdown_get_list(ui->TH_Settings_lowddlist_3), &style_TH_Settings_lowddlist_3_extra_list_scrollbar_default, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

    //Write codes TH_Settings_Temperature
    ui->TH_Settings_Temperature = lv_label_create(ui->TH_Settings_T_lable);
    lv_label_set_text(ui->TH_Settings_Temperature, "Temperature\n");
    lv_label_set_long_mode(ui->TH_Settings_Temperature, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->TH_Settings_Temperature, 31, 12);
    lv_obj_set_size(ui->TH_Settings_Temperature, 151, 28);

    //Write style for TH_Settings_Temperature, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->TH_Settings_Temperature, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->TH_Settings_Temperature, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->TH_Settings_Temperature, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->TH_Settings_Temperature, &lv_font_montserratMedium_21, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->TH_Settings_Temperature, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->TH_Settings_Temperature, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->TH_Settings_Temperature, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->TH_Settings_Temperature, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->TH_Settings_Temperature, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->TH_Settings_Temperature, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->TH_Settings_Temperature, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->TH_Settings_Temperature, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->TH_Settings_Temperature, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->TH_Settings_Temperature, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes TH_Settings_lowlabel_3
    ui->TH_Settings_lowlabel_3 = lv_label_create(ui->TH_Settings_T_lable);
    lv_label_set_text(ui->TH_Settings_lowlabel_3, "L:\n");
    lv_label_set_long_mode(ui->TH_Settings_lowlabel_3, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->TH_Settings_lowlabel_3, 237, 16);
    lv_obj_set_size(ui->TH_Settings_lowlabel_3, 38, 24);

    //Write style for TH_Settings_lowlabel_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->TH_Settings_lowlabel_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->TH_Settings_lowlabel_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->TH_Settings_lowlabel_3, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->TH_Settings_lowlabel_3, &lv_font_montserratMedium_21, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->TH_Settings_lowlabel_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->TH_Settings_lowlabel_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->TH_Settings_lowlabel_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->TH_Settings_lowlabel_3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->TH_Settings_lowlabel_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->TH_Settings_lowlabel_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->TH_Settings_lowlabel_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->TH_Settings_lowlabel_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->TH_Settings_lowlabel_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->TH_Settings_lowlabel_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes TH_Settings_highddlist_3
    ui->TH_Settings_highddlist_3 = lv_dropdown_create(ui->TH_Settings_T_lable);
    lv_dropdown_set_options(ui->TH_Settings_highddlist_3, "-20\n-15\n-10\n-5\n0\n5\n10\n15\n20\n25\n30\n40\n50\n60");
		//lv_dropdown_set_selected(ui->TH_Settings_highddlist_3, 10);
    lv_obj_set_pos(ui->TH_Settings_highddlist_3, 386, 15);
    lv_obj_set_size(ui->TH_Settings_highddlist_3, 52, 25);

    //Write style for TH_Settings_highddlist_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->TH_Settings_highddlist_3, lv_color_hex(0x0D3055), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->TH_Settings_highddlist_3, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->TH_Settings_highddlist_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->TH_Settings_highddlist_3, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->TH_Settings_highddlist_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->TH_Settings_highddlist_3, lv_color_hex(0xe1e6ee), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->TH_Settings_highddlist_3, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->TH_Settings_highddlist_3, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->TH_Settings_highddlist_3, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->TH_Settings_highddlist_3, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->TH_Settings_highddlist_3, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->TH_Settings_highddlist_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->TH_Settings_highddlist_3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->TH_Settings_highddlist_3, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->TH_Settings_highddlist_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_CHECKED for &style_TH_Settings_highddlist_3_extra_list_selected_checked
    static lv_style_t style_TH_Settings_highddlist_3_extra_list_selected_checked;
    ui_init_style(&style_TH_Settings_highddlist_3_extra_list_selected_checked);

    lv_style_set_border_width(&style_TH_Settings_highddlist_3_extra_list_selected_checked, 1);
    lv_style_set_border_opa(&style_TH_Settings_highddlist_3_extra_list_selected_checked, 255);
    lv_style_set_border_color(&style_TH_Settings_highddlist_3_extra_list_selected_checked, lv_color_hex(0xe1e6ee));
    lv_style_set_border_side(&style_TH_Settings_highddlist_3_extra_list_selected_checked, LV_BORDER_SIDE_FULL);
    lv_style_set_radius(&style_TH_Settings_highddlist_3_extra_list_selected_checked, 3);
    lv_style_set_bg_opa(&style_TH_Settings_highddlist_3_extra_list_selected_checked, 255);
    lv_style_set_bg_color(&style_TH_Settings_highddlist_3_extra_list_selected_checked, lv_color_hex(0x00a1b5));
    lv_style_set_bg_grad_dir(&style_TH_Settings_highddlist_3_extra_list_selected_checked, LV_GRAD_DIR_NONE);
    lv_obj_add_style(lv_dropdown_get_list(ui->TH_Settings_highddlist_3), &style_TH_Settings_highddlist_3_extra_list_selected_checked, LV_PART_SELECTED|LV_STATE_CHECKED);

    //Write style state: LV_STATE_DEFAULT for &style_TH_Settings_highddlist_3_extra_list_main_default
    static lv_style_t style_TH_Settings_highddlist_3_extra_list_main_default;
    ui_init_style(&style_TH_Settings_highddlist_3_extra_list_main_default);

    lv_style_set_max_height(&style_TH_Settings_highddlist_3_extra_list_main_default, 90);
    lv_style_set_text_color(&style_TH_Settings_highddlist_3_extra_list_main_default, lv_color_hex(0x0D3055));
    lv_style_set_text_font(&style_TH_Settings_highddlist_3_extra_list_main_default, &lv_font_montserratMedium_12);
    lv_style_set_text_opa(&style_TH_Settings_highddlist_3_extra_list_main_default, 255);
    lv_style_set_border_width(&style_TH_Settings_highddlist_3_extra_list_main_default, 1);
    lv_style_set_border_opa(&style_TH_Settings_highddlist_3_extra_list_main_default, 255);
    lv_style_set_border_color(&style_TH_Settings_highddlist_3_extra_list_main_default, lv_color_hex(0xe1e6ee));
    lv_style_set_border_side(&style_TH_Settings_highddlist_3_extra_list_main_default, LV_BORDER_SIDE_FULL);
    lv_style_set_radius(&style_TH_Settings_highddlist_3_extra_list_main_default, 3);
    lv_style_set_bg_opa(&style_TH_Settings_highddlist_3_extra_list_main_default, 255);
    lv_style_set_bg_color(&style_TH_Settings_highddlist_3_extra_list_main_default, lv_color_hex(0xffffff));
    lv_style_set_bg_grad_dir(&style_TH_Settings_highddlist_3_extra_list_main_default, LV_GRAD_DIR_NONE);
    lv_obj_add_style(lv_dropdown_get_list(ui->TH_Settings_highddlist_3), &style_TH_Settings_highddlist_3_extra_list_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_TH_Settings_highddlist_3_extra_list_scrollbar_default
    static lv_style_t style_TH_Settings_highddlist_3_extra_list_scrollbar_default;
    ui_init_style(&style_TH_Settings_highddlist_3_extra_list_scrollbar_default);

    lv_style_set_radius(&style_TH_Settings_highddlist_3_extra_list_scrollbar_default, 3);
    lv_style_set_bg_opa(&style_TH_Settings_highddlist_3_extra_list_scrollbar_default, 255);
    lv_style_set_bg_color(&style_TH_Settings_highddlist_3_extra_list_scrollbar_default, lv_color_hex(0x00ff00));
    lv_style_set_bg_grad_dir(&style_TH_Settings_highddlist_3_extra_list_scrollbar_default, LV_GRAD_DIR_NONE);
    lv_obj_add_style(lv_dropdown_get_list(ui->TH_Settings_highddlist_3), &style_TH_Settings_highddlist_3_extra_list_scrollbar_default, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

    //Write codes TH_Settings_NTU
    ui->TH_Settings_NTU = lv_obj_create(ui->TH_Settings_Setting);
    lv_obj_set_pos(ui->TH_Settings_NTU, 7, 182);
    lv_obj_set_size(ui->TH_Settings_NTU, 465, 48);
    lv_obj_set_scrollbar_mode(ui->TH_Settings_NTU, LV_SCROLLBAR_MODE_OFF);

    //Write style for TH_Settings_NTU, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->TH_Settings_NTU, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->TH_Settings_NTU, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->TH_Settings_NTU, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->TH_Settings_NTU, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->TH_Settings_NTU, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->TH_Settings_NTU, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->TH_Settings_NTU, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->TH_Settings_NTU, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->TH_Settings_NTU, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->TH_Settings_NTU, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes TH_Settings_highddlist_4
    ui->TH_Settings_highddlist_4 = lv_dropdown_create(ui->TH_Settings_NTU);
    lv_dropdown_set_options(ui->TH_Settings_highddlist_4, "0\n1\n2\n3\n4\n5");
    lv_obj_set_pos(ui->TH_Settings_highddlist_4, 386, 12);
    lv_obj_set_size(ui->TH_Settings_highddlist_4, 50, 25);

    //Write style for TH_Settings_highddlist_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->TH_Settings_highddlist_4, lv_color_hex(0x0D3055), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->TH_Settings_highddlist_4, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->TH_Settings_highddlist_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->TH_Settings_highddlist_4, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->TH_Settings_highddlist_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->TH_Settings_highddlist_4, lv_color_hex(0xe1e6ee), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->TH_Settings_highddlist_4, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->TH_Settings_highddlist_4, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->TH_Settings_highddlist_4, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->TH_Settings_highddlist_4, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->TH_Settings_highddlist_4, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->TH_Settings_highddlist_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->TH_Settings_highddlist_4, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->TH_Settings_highddlist_4, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->TH_Settings_highddlist_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_CHECKED for &style_TH_Settings_highddlist_4_extra_list_selected_checked
    static lv_style_t style_TH_Settings_highddlist_4_extra_list_selected_checked;
    ui_init_style(&style_TH_Settings_highddlist_4_extra_list_selected_checked);

    lv_style_set_border_width(&style_TH_Settings_highddlist_4_extra_list_selected_checked, 1);
    lv_style_set_border_opa(&style_TH_Settings_highddlist_4_extra_list_selected_checked, 255);
    lv_style_set_border_color(&style_TH_Settings_highddlist_4_extra_list_selected_checked, lv_color_hex(0xe1e6ee));
    lv_style_set_border_side(&style_TH_Settings_highddlist_4_extra_list_selected_checked, LV_BORDER_SIDE_FULL);
    lv_style_set_radius(&style_TH_Settings_highddlist_4_extra_list_selected_checked, 3);
    lv_style_set_bg_opa(&style_TH_Settings_highddlist_4_extra_list_selected_checked, 255);
    lv_style_set_bg_color(&style_TH_Settings_highddlist_4_extra_list_selected_checked, lv_color_hex(0x00a1b5));
    lv_style_set_bg_grad_dir(&style_TH_Settings_highddlist_4_extra_list_selected_checked, LV_GRAD_DIR_NONE);
    lv_obj_add_style(lv_dropdown_get_list(ui->TH_Settings_highddlist_4), &style_TH_Settings_highddlist_4_extra_list_selected_checked, LV_PART_SELECTED|LV_STATE_CHECKED);

    //Write style state: LV_STATE_DEFAULT for &style_TH_Settings_highddlist_4_extra_list_main_default
    static lv_style_t style_TH_Settings_highddlist_4_extra_list_main_default;
    ui_init_style(&style_TH_Settings_highddlist_4_extra_list_main_default);

    lv_style_set_max_height(&style_TH_Settings_highddlist_4_extra_list_main_default, 90);
    lv_style_set_text_color(&style_TH_Settings_highddlist_4_extra_list_main_default, lv_color_hex(0x0D3055));
    lv_style_set_text_font(&style_TH_Settings_highddlist_4_extra_list_main_default, &lv_font_montserratMedium_12);
    lv_style_set_text_opa(&style_TH_Settings_highddlist_4_extra_list_main_default, 255);
    lv_style_set_border_width(&style_TH_Settings_highddlist_4_extra_list_main_default, 1);
    lv_style_set_border_opa(&style_TH_Settings_highddlist_4_extra_list_main_default, 255);
    lv_style_set_border_color(&style_TH_Settings_highddlist_4_extra_list_main_default, lv_color_hex(0xe1e6ee));
    lv_style_set_border_side(&style_TH_Settings_highddlist_4_extra_list_main_default, LV_BORDER_SIDE_FULL);
    lv_style_set_radius(&style_TH_Settings_highddlist_4_extra_list_main_default, 3);
    lv_style_set_bg_opa(&style_TH_Settings_highddlist_4_extra_list_main_default, 255);
    lv_style_set_bg_color(&style_TH_Settings_highddlist_4_extra_list_main_default, lv_color_hex(0xffffff));
    lv_style_set_bg_grad_dir(&style_TH_Settings_highddlist_4_extra_list_main_default, LV_GRAD_DIR_NONE);
    lv_obj_add_style(lv_dropdown_get_list(ui->TH_Settings_highddlist_4), &style_TH_Settings_highddlist_4_extra_list_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_TH_Settings_highddlist_4_extra_list_scrollbar_default
    static lv_style_t style_TH_Settings_highddlist_4_extra_list_scrollbar_default;
    ui_init_style(&style_TH_Settings_highddlist_4_extra_list_scrollbar_default);

    lv_style_set_radius(&style_TH_Settings_highddlist_4_extra_list_scrollbar_default, 3);
    lv_style_set_bg_opa(&style_TH_Settings_highddlist_4_extra_list_scrollbar_default, 255);
    lv_style_set_bg_color(&style_TH_Settings_highddlist_4_extra_list_scrollbar_default, lv_color_hex(0x00ff00));
    lv_style_set_bg_grad_dir(&style_TH_Settings_highddlist_4_extra_list_scrollbar_default, LV_GRAD_DIR_NONE);
    lv_obj_add_style(lv_dropdown_get_list(ui->TH_Settings_highddlist_4), &style_TH_Settings_highddlist_4_extra_list_scrollbar_default, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

    //Write codes TH_Settings_ntu
    ui->TH_Settings_ntu = lv_label_create(ui->TH_Settings_NTU);
    lv_label_set_text(ui->TH_Settings_ntu, "NTU\n");
    lv_label_set_long_mode(ui->TH_Settings_ntu, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->TH_Settings_ntu, 30, 13);
    lv_obj_set_size(ui->TH_Settings_ntu, 63, 32);

    //Write style for TH_Settings_ntu, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->TH_Settings_ntu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->TH_Settings_ntu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->TH_Settings_ntu, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->TH_Settings_ntu, &lv_font_montserratMedium_21, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->TH_Settings_ntu, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->TH_Settings_ntu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->TH_Settings_ntu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->TH_Settings_ntu, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->TH_Settings_ntu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->TH_Settings_ntu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->TH_Settings_ntu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->TH_Settings_ntu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->TH_Settings_ntu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->TH_Settings_ntu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of TH_Settings.
		lv_dropdown_set_selected(guider_ui.TH_Settings_highddlist_4, SettingData.NTU_H);
		lv_dropdown_set_selected(guider_ui.TH_Settings_lowlist, (int)SettingData.PH_L);
		lv_dropdown_set_selected(guider_ui.TH_Settings_high_list, (int)SettingData.PH_H);
		lv_dropdown_set_selected(guider_ui.TH_Settings_highlist_2, ((SettingData.TDS_H-100)/100));
		lv_dropdown_set_selected(guider_ui.TH_Settings_highddlist_3, temperature_to_index(SettingData.Temperature_H));
    lv_dropdown_set_selected(guider_ui.TH_Settings_lowddlist_3, temperature_to_index(SettingData.Temperature_L));
						

    //Update current screen layout.
    lv_obj_update_layout(ui->TH_Settings);

    //Init events for screen.
    events_init_TH_Settings(ui);
}
