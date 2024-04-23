#include <gui_game_mode_menu.hpp>
#include <Arduino.h>
void gui_game_mode_menu_create(
    gui_game_mode_menu* mode_menu,
    lv_obj_t* parent,
    gui_menu* difficulty_menue
){
    gui_game_mode_menue_create_div(mode_menu, parent);
    gui_game_mode_menue_create_header(mode_menu, mode_menu->div);
    gui_game_mode_menu_create_singleplayer_button(
        mode_menu, mode_menu->div,
        lv_color_white(),
        lv_color_black() 
    );
    gui_game_mode_menu_create_multiplayer_button(
        mode_menu, mode_menu->div,
        lv_color_white(),
        lv_color_black() 
    );

    mode_menu->difficulty_menue = difficulty_menue;
    mode_menu->difficulty_menue->mode_menu = mode_menu;
}

void gui_game_mode_menue_create_div(gui_game_mode_menu* mode_menu, lv_obj_t* parent){
    mode_menu->div = lv_obj_create(parent);
    
    lv_obj_set_style_text_font(mode_menu->div, &lv_font_montserrat_32, 0);
    lv_obj_set_style_opa(mode_menu->div,255,0);
    lv_obj_set_size(mode_menu->div, 320, 480);
    lv_obj_set_style_border_width(mode_menu->div, 0, 0);
    lv_obj_set_style_radius(mode_menu->div, 0, 0);
    lv_obj_set_style_bg_color(mode_menu->div, lv_color_make(247,197,102), 0);
    
}

void gui_game_mode_menu_create_singleplayer_button(
    gui_game_mode_menu* mode_menu,
    lv_obj_t* parent,
    lv_color_t color_text,
    lv_color_t color_bg
){
    mode_menu->singleplayer_button = lv_btn_create(mode_menu->div);
    lv_obj_t* label = lv_label_create(mode_menu->singleplayer_button);
    lv_label_set_text_fmt(label, "Singleplayer");
    lv_obj_set_style_bg_color(mode_menu->singleplayer_button, color_bg, 0);
    lv_obj_set_style_text_color(mode_menu->singleplayer_button, color_text, 0);
    lv_obj_align(mode_menu->singleplayer_button, LV_ALIGN_CENTER, 0, -50);
    //Add cb
    lv_obj_add_event_cb(
        mode_menu->singleplayer_button,
        gui_game_mode_menue_singleplayer_button_cb,
        LV_EVENT_ALL,
        mode_menu
    );



}

void gui_game_mode_menu_create_multiplayer_button(
    gui_game_mode_menu* mode_menu,
    lv_obj_t* parent,
    lv_color_t color_text,
    lv_color_t color_bg
){
    mode_menu->multiplayer_button = lv_btn_create(mode_menu->div);
    lv_obj_t* label = lv_label_create(mode_menu->multiplayer_button);
    lv_label_set_text_fmt(label, "Multiplayer");
    lv_obj_set_style_bg_color(mode_menu->multiplayer_button, color_bg, 0);
    lv_obj_set_style_text_color(mode_menu->multiplayer_button, color_text, 0);
    lv_obj_align(mode_menu->multiplayer_button, LV_ALIGN_CENTER, 0, 70);   
    // Add cb
    lv_obj_add_event_cb(
        mode_menu->multiplayer_button,
        gui_game_mode_menue_multiplayer_button_cb,
        LV_EVENT_ALL,
        mode_menu
    );
}

void gui_game_mode_menue_create_header(gui_game_mode_menu* mode_menu, lv_obj_t* parent){
    mode_menu->header = lv_label_create(mode_menu->div);
    lv_label_set_text_fmt(mode_menu->header, "MINESWEEPER");
    lv_obj_set_style_text_font(mode_menu->header, &lv_font_montserrat_32, 0);
    lv_obj_align(mode_menu->header, LV_ALIGN_TOP_MID, 0, 50);
}

void gui_game_mode_menue_singleplayer_button_cb(lv_event_t* e){
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t* obj = lv_event_get_target(e);
    gui_game_mode_menu* mode_menu = (gui_game_mode_menu*)lv_event_get_user_data(e);
    if(code == LV_EVENT_CLICKED){
        gui_menu_singleplayer(mode_menu->difficulty_menue);
        gui_game_mode_menue_hide(mode_menu);
    }
}

void gui_game_mode_menue_multiplayer_button_cb(lv_event_t* e){
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t* obj = lv_event_get_target(e);
    gui_game_mode_menu* mode_menu = (gui_game_mode_menu*)lv_event_get_user_data(e);
    if(code == LV_EVENT_CLICKED){
        //wifi_init(mode_menu->difficulty_menue);
        gui_menu_multiplayer(mode_menu->difficulty_menue);
        Serial.println("Starting multiplayer");
        gui_game_mode_menue_hide(mode_menu);
    }
}


void gui_game_mode_menue_show(gui_game_mode_menu* mode_menu){
    lv_obj_clear_flag(mode_menu->div, LV_OBJ_FLAG_HIDDEN);
}

void gui_game_mode_menue_hide(gui_game_mode_menu* mode_menu){
    lv_obj_add_flag(mode_menu->div, LV_OBJ_FLAG_HIDDEN);
}