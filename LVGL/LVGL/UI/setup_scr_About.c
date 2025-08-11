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




void setup_scr_About(lv_ui *ui)
{
    //Write codes About
    ui->About = lv_obj_create(NULL);
    lv_obj_set_size(ui->About, 480, 272);
    lv_obj_set_scrollbar_mode(ui->About, LV_SCROLLBAR_MODE_OFF);

    //Write style for About, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->About, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes About_Slider
    ui->About_Slider = lv_obj_create(ui->About);
    lv_obj_set_pos(ui->About_Slider, 0, 50);
    lv_obj_set_size(ui->About_Slider, 480, 222);
    lv_obj_set_scrollbar_mode(ui->About_Slider, LV_SCROLLBAR_MODE_AUTO);

    //Write style for About_Slider, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->About_Slider, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->About_Slider, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->About_Slider, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->About_Slider, lv_color_hex(0xe2e2e2), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->About_Slider, LV_GRAD_DIR_VER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui->About_Slider, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_main_stop(ui->About_Slider, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_stop(ui->About_Slider, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->About_Slider, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->About_Slider, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->About_Slider, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->About_Slider, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->About_Slider, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes About_AboutText
    ui->About_AboutText = lv_obj_create(ui->About_Slider);
    lv_obj_set_pos(ui->About_AboutText, 7, 10);
    lv_obj_set_size(ui->About_AboutText, 465, 205);
    lv_obj_set_scrollbar_mode(ui->About_AboutText, LV_SCROLLBAR_MODE_ON);

    //Write style for About_AboutText, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->About_AboutText, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->About_AboutText, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->About_AboutText, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->About_AboutText, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->About_AboutText, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->About_AboutText, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->About_AboutText, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->About_AboutText, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->About_AboutText, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->About_AboutText, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes About_label_1
    ui->About_label_1 = lv_label_create(ui->About_AboutText);
    lv_label_set_text(ui->About_label_1, "Author:Qiu Zhenbang");
    lv_label_set_long_mode(ui->About_label_1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->About_label_1, 15, 16);
    lv_obj_set_size(ui->About_label_1, 423, 57);

    //Write style for About_label_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->About_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->About_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->About_label_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->About_label_1, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->About_label_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->About_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->About_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->About_label_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->About_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->About_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->About_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->About_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->About_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->About_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes About_AboutTitle
    ui->About_AboutTitle = lv_obj_create(ui->About);
    lv_obj_set_pos(ui->About_AboutTitle, 0, 0);
    lv_obj_set_size(ui->About_AboutTitle, 480, 50);
    lv_obj_set_scrollbar_mode(ui->About_AboutTitle, LV_SCROLLBAR_MODE_OFF);

    //Write style for About_AboutTitle, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->About_AboutTitle, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->About_AboutTitle, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->About_AboutTitle, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->About_AboutTitle, lv_color_hex(0x62b4e4), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->About_AboutTitle, LV_GRAD_DIR_HOR, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui->About_AboutTitle, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_main_stop(ui->About_AboutTitle, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_stop(ui->About_AboutTitle, 177, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->About_AboutTitle, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->About_AboutTitle, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->About_AboutTitle, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->About_AboutTitle, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->About_AboutTitle, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes About_About_button_back
    ui->About_About_button_back = lv_btn_create(ui->About_AboutTitle);
    ui->About_About_button_back_label = lv_label_create(ui->About_About_button_back);
    lv_label_set_text(ui->About_About_button_back_label, "Back");
    lv_label_set_long_mode(ui->About_About_button_back_label, LV_LABEL_LONG_SCROLL);
    lv_obj_align(ui->About_About_button_back_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->About_About_button_back, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->About_About_button_back_label, LV_PCT(100));
    lv_obj_set_pos(ui->About_About_button_back, 13, 6);
    lv_obj_set_size(ui->About_About_button_back, 87, 34);

    //Write style for About_About_button_back, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->About_About_button_back, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->About_About_button_back, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->About_About_button_back, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->About_About_button_back, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->About_About_button_back, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->About_About_button_back, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->About_About_button_back, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->About_About_button_back, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->About_About_button_back, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->About_About_button_back, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of About.


    //Update current screen layout.
    lv_obj_update_layout(ui->About);

    //Init events for screen.
    events_init_About(ui);
}
