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



lv_obj_t *Log_log_win_label;
void setup_scr_Log(lv_ui *ui)
{
    //Write codes Log
    ui->Log = lv_obj_create(NULL);
    lv_obj_set_size(ui->Log, 480, 272);
    lv_obj_set_scrollbar_mode(ui->Log, LV_SCROLLBAR_MODE_OFF);

    //Write style for Log, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Log, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Log_log_win
    ui->Log_log_win = lv_win_create(ui->Log, 40);
    lv_obj_t * Log_log_win_title = lv_win_add_title(ui->Log_log_win, "Log");
    ui->Log_log_win_item0 = lv_win_add_btn(ui->Log_log_win, LV_SYMBOL_UP, 40);
		Log_log_win_label = lv_label_create(lv_win_get_content(ui->Log_log_win));
		lv_label_set_text(Log_log_win_label, "");
    lv_obj_set_scrollbar_mode(lv_win_get_content(ui->Log_log_win), LV_SCROLLBAR_MODE_AUTO);
    lv_obj_set_pos(ui->Log_log_win, 0, 0);
    lv_obj_set_size(ui->Log_log_win, 480, 272);
    lv_obj_set_scrollbar_mode(ui->Log_log_win, LV_SCROLLBAR_MODE_AUTO);

    //Write style for Log_log_win, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Log_log_win, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Log_log_win, lv_color_hex(0xeeeef6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->Log_log_win, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui->Log_log_win, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Log_log_win, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_Log_log_win_extra_content_main_default
    static lv_style_t style_Log_log_win_extra_content_main_default;
    ui_init_style(&style_Log_log_win_extra_content_main_default);

    lv_style_set_bg_opa(&style_Log_log_win_extra_content_main_default, 255);
    lv_style_set_bg_color(&style_Log_log_win_extra_content_main_default, lv_color_hex(0xeeeef6));
    lv_style_set_bg_grad_dir(&style_Log_log_win_extra_content_main_default, LV_GRAD_DIR_NONE);
    lv_style_set_text_color(&style_Log_log_win_extra_content_main_default, lv_color_hex(0x393c41));
    lv_style_set_text_font(&style_Log_log_win_extra_content_main_default, &lv_font_montserratMedium_12);
    lv_style_set_text_opa(&style_Log_log_win_extra_content_main_default, 255);
    lv_style_set_text_letter_space(&style_Log_log_win_extra_content_main_default, 0);
    lv_style_set_text_line_space(&style_Log_log_win_extra_content_main_default, 2);
    lv_obj_add_style(lv_win_get_content(ui->Log_log_win), &style_Log_log_win_extra_content_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_Log_log_win_extra_header_main_default
    static lv_style_t style_Log_log_win_extra_header_main_default;
    ui_init_style(&style_Log_log_win_extra_header_main_default);

    lv_style_set_bg_opa(&style_Log_log_win_extra_header_main_default, 255);
    lv_style_set_bg_color(&style_Log_log_win_extra_header_main_default, lv_color_hex(0xe6e6e6));
    lv_style_set_bg_grad_dir(&style_Log_log_win_extra_header_main_default, LV_GRAD_DIR_NONE);
    lv_style_set_text_color(&style_Log_log_win_extra_header_main_default, lv_color_hex(0x393c41));
    lv_style_set_text_font(&style_Log_log_win_extra_header_main_default, &lv_font_montserratMedium_12);
    lv_style_set_text_opa(&style_Log_log_win_extra_header_main_default, 255);
    lv_style_set_text_letter_space(&style_Log_log_win_extra_header_main_default, 0);
    lv_style_set_text_line_space(&style_Log_log_win_extra_header_main_default, 2);
    lv_style_set_pad_top(&style_Log_log_win_extra_header_main_default, 5);
    lv_style_set_pad_right(&style_Log_log_win_extra_header_main_default, 5);
    lv_style_set_pad_bottom(&style_Log_log_win_extra_header_main_default, 5);
    lv_style_set_pad_left(&style_Log_log_win_extra_header_main_default, 5);
    lv_style_set_pad_column(&style_Log_log_win_extra_header_main_default, 5);
    lv_obj_add_style(lv_win_get_header(ui->Log_log_win), &style_Log_log_win_extra_header_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_Log_log_win_extra_btns_main_default
    static lv_style_t style_Log_log_win_extra_btns_main_default;
    ui_init_style(&style_Log_log_win_extra_btns_main_default);

    lv_style_set_radius(&style_Log_log_win_extra_btns_main_default, 8);
    lv_style_set_border_width(&style_Log_log_win_extra_btns_main_default, 0);
    lv_style_set_bg_opa(&style_Log_log_win_extra_btns_main_default, 255);
    lv_style_set_bg_color(&style_Log_log_win_extra_btns_main_default, lv_color_hex(0x2195f6));
    lv_style_set_bg_grad_dir(&style_Log_log_win_extra_btns_main_default, LV_GRAD_DIR_NONE);
    lv_style_set_shadow_width(&style_Log_log_win_extra_btns_main_default, 0);
    lv_obj_add_style(ui->Log_log_win_item0, &style_Log_log_win_extra_btns_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of Log.


    //Update current screen layout.
    lv_obj_update_layout(ui->Log);

    //Init events for screen.
    events_init_Log(ui);
}
