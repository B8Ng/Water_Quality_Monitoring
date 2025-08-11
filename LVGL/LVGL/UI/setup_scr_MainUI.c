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
#include "FreeRTOS.h"
#include "queue.h"



int MainUI_digital_clock_1_min_value = 45;
int MainUI_digital_clock_1_hour_value = 23;
int MainUI_digital_clock_1_sec_value = 57;
uint8_t NodeNumber = 0;


void setup_scr_MainUI(lv_ui *ui)
{

	
    //Write codes MainUI
    ui->MainUI = lv_obj_create(NULL);
    lv_obj_set_size(ui->MainUI, 480, 272);
    lv_obj_set_scrollbar_mode(ui->MainUI, LV_SCROLLBAR_MODE_OFF);

    //Write style for MainUI, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->MainUI, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes MainUI_cont_1
    ui->MainUI_cont_1 = lv_obj_create(ui->MainUI);
    lv_obj_set_pos(ui->MainUI_cont_1, 0, 0);
    lv_obj_set_size(ui->MainUI_cont_1, 480, 272);
    lv_obj_set_scrollbar_mode(ui->MainUI_cont_1, LV_SCROLLBAR_MODE_OFF);

    //Write style for MainUI_cont_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->MainUI_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MainUI_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->MainUI_cont_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->MainUI_cont_1, lv_color_hex(0xf5f5f5), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->MainUI_cont_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->MainUI_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->MainUI_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->MainUI_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->MainUI_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MainUI_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes MainUI_Node
    ui->MainUI_Node = lv_obj_create(ui->MainUI_cont_1);
    lv_obj_set_pos(ui->MainUI_Node, 178, 128);
    lv_obj_set_size(ui->MainUI_Node, 280, 125);
    lv_obj_set_scrollbar_mode(ui->MainUI_Node, LV_SCROLLBAR_MODE_OFF);

    //Write style for MainUI_Node, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->MainUI_Node, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MainUI_Node, 12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->MainUI_Node, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->MainUI_Node, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->MainUI_Node, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->MainUI_Node, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->MainUI_Node, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->MainUI_Node, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->MainUI_Node, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MainUI_Node, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui->MainUI_Node, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui->MainUI_Node, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui->MainUI_Node, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(ui->MainUI_Node, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(ui->MainUI_Node, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes MainUI_img_1
    ui->MainUI_img_1 = lv_img_create(ui->MainUI_Node);
    lv_obj_add_flag(ui->MainUI_img_1, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->MainUI_img_1, &_node_alpha_32x32);
    lv_img_set_pivot(ui->MainUI_img_1, 50,50);
    lv_img_set_angle(ui->MainUI_img_1, 0);
    lv_obj_set_pos(ui->MainUI_img_1, 14, 11);
    lv_obj_set_size(ui->MainUI_img_1, 32, 32);

    //Write style for MainUI_img_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->MainUI_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->MainUI_img_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MainUI_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->MainUI_img_1, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes MainUI_node_num
    ui->MainUI_node_num = lv_label_create(ui->MainUI_Node);

		lv_label_set_text(ui->MainUI_node_num, "Node Num: 0"); 
		
   
    lv_label_set_long_mode(ui->MainUI_node_num, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->MainUI_node_num, 67, 20);
    lv_obj_set_size(ui->MainUI_node_num, 158, 22);

    //Write style for MainUI_node_num, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->MainUI_node_num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MainUI_node_num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->MainUI_node_num, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->MainUI_node_num, &lv_font_Acme_Regular_21, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->MainUI_node_num, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->MainUI_node_num, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->MainUI_node_num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->MainUI_node_num, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->MainUI_node_num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->MainUI_node_num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->MainUI_node_num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->MainUI_node_num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->MainUI_node_num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MainUI_node_num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes MainUI_connect
    ui->MainUI_connect = lv_label_create(ui->MainUI_Node);
    lv_label_set_text(ui->MainUI_connect, "Network : NC");
    lv_label_set_long_mode(ui->MainUI_connect, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->MainUI_connect, 65, 57);
    lv_obj_set_size(ui->MainUI_connect, 158, 22);

    //Write style for MainUI_connect, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->MainUI_connect, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MainUI_connect, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->MainUI_connect, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->MainUI_connect, &lv_font_Acme_Regular_21, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->MainUI_connect, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->MainUI_connect, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->MainUI_connect, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->MainUI_connect, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->MainUI_connect, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->MainUI_connect, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->MainUI_connect, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->MainUI_connect, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->MainUI_connect, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MainUI_connect, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes MainUI_log
    ui->MainUI_log = lv_label_create(ui->MainUI_Node);
    lv_label_set_text(ui->MainUI_log, "Log warning: 0");
    lv_label_set_long_mode(ui->MainUI_log, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->MainUI_log, 72, 91);
    lv_obj_set_size(ui->MainUI_log, 158, 22);

    //Write style for MainUI_log, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->MainUI_log, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MainUI_log, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->MainUI_log, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->MainUI_log, &lv_font_Acme_Regular_21, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->MainUI_log, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->MainUI_log, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->MainUI_log, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->MainUI_log, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->MainUI_log, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->MainUI_log, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->MainUI_log, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->MainUI_log, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->MainUI_log, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MainUI_log, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes MainUI_Settingicon
    ui->MainUI_Settingicon = lv_imgbtn_create(ui->MainUI);
    lv_obj_add_flag(ui->MainUI_Settingicon, LV_OBJ_FLAG_CHECKABLE);
    lv_imgbtn_set_src(ui->MainUI_Settingicon, LV_IMGBTN_STATE_RELEASED, NULL, &_setting_alpha_32x32, NULL);
    lv_imgbtn_set_src(ui->MainUI_Settingicon, LV_IMGBTN_STATE_PRESSED, NULL, &_setting_alpha_32x32, NULL);
    lv_imgbtn_set_src(ui->MainUI_Settingicon, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, &_setting_alpha_32x32, NULL);
    lv_imgbtn_set_src(ui->MainUI_Settingicon, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, &_setting_alpha_32x32, NULL);
    ui->MainUI_Settingicon_label = lv_label_create(ui->MainUI_Settingicon);
    lv_label_set_text(ui->MainUI_Settingicon_label, "");
    lv_label_set_long_mode(ui->MainUI_Settingicon_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->MainUI_Settingicon_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->MainUI_Settingicon, 0, LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->MainUI_Settingicon, 434, 10);
    lv_obj_set_size(ui->MainUI_Settingicon, 32, 32);

    //Write style for MainUI_Settingicon, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->MainUI_Settingicon, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->MainUI_Settingicon, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->MainUI_Settingicon, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->MainUI_Settingicon, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MainUI_Settingicon, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->MainUI_Settingicon, true, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MainUI_Settingicon, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for MainUI_Settingicon, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_img_recolor_opa(ui->MainUI_Settingicon, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_img_opa(ui->MainUI_Settingicon, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->MainUI_Settingicon, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->MainUI_Settingicon, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->MainUI_Settingicon, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->MainUI_Settingicon, 0, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write style for MainUI_Settingicon, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
    lv_obj_set_style_img_recolor_opa(ui->MainUI_Settingicon, 0, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_img_opa(ui->MainUI_Settingicon, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->MainUI_Settingicon, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->MainUI_Settingicon, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_opa(ui->MainUI_Settingicon, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->MainUI_Settingicon, 0, LV_PART_MAIN|LV_STATE_CHECKED);

    //Write style for MainUI_Settingicon, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
    lv_obj_set_style_img_recolor_opa(ui->MainUI_Settingicon, 0, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);
    lv_obj_set_style_img_opa(ui->MainUI_Settingicon, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

    //Write codes MainUI_digital_clock_1
    static bool MainUI_digital_clock_1_timer_enabled = false;
    ui->MainUI_digital_clock_1 = lv_dclock_create(ui->MainUI, "");
    if (!MainUI_digital_clock_1_timer_enabled) {
        lv_timer_create(MainUI_digital_clock_1_timer, 1000, NULL);
        MainUI_digital_clock_1_timer_enabled = true;
    }
    lv_obj_set_pos(ui->MainUI_digital_clock_1, 20, 20);
    lv_obj_set_size(ui->MainUI_digital_clock_1, 250, 90);

    //Write style for MainUI_digital_clock_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_radius(ui->MainUI_digital_clock_1, 12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->MainUI_digital_clock_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->MainUI_digital_clock_1, &lv_font_Acme_Regular_80, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->MainUI_digital_clock_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->MainUI_digital_clock_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->MainUI_digital_clock_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->MainUI_digital_clock_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->MainUI_digital_clock_1, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->MainUI_digital_clock_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->MainUI_digital_clock_1, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->MainUI_digital_clock_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->MainUI_digital_clock_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->MainUI_digital_clock_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MainUI_digital_clock_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of MainUI.
		

    //Update current screen layout.
    lv_obj_update_layout(ui->MainUI);

    //Init events for screen.
    events_init_MainUI(ui);
}

