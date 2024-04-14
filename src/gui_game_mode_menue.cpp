#include <gui_game_mode_menue.hpp>

void game_mode_menue_create(
    game_mode_menue* mode_menu,
    lv_obj_t* parent,
    gui_menue* difficulty_menue
){
    game_mode_menue_create_div(mode_menu, parent);
}

void game_mode_menue_create_div(game_mode_menue* mode_menu, lv_obj_t* parent){
    mode_menu->div = lv_obj_create(parent);
    
    lv_obj_remove_style_all(mode_menu->div);
    lv_obj_set_size(mode_menu->div, 320, 480);
    lv_obj_set_style_bg_color(mode_menu->div, lv_color_make(247,197,102), 0);

}

void game_mode_menue_create_singleplayer_button(
    game_mode_menue* mode_menu,
    lv_obj_t* parent,
    lv_color_t color_text,
    lv_color_t color_bg
){
    mode_menu->singleplayer_button = lv_btn_create(mode_menu->div);
    lv_obj_t* label = lv_label_create(mode_menu->singleplayer_button);
    lv_label_set_text_fmt(label, "Singleplayer");
    lv_obj_set_style_bg_color(mode_menu->singleplayer_button, color_bg, 0);
    lv_obj_set_style_text_color(mode_menu->singleplayer_button, color_text, 0);
    lv_obj_align(mode_menu->singleplayer_button, LV_ALIGN_CENTER, 0, 0);
    //Add cb
}

void game_mode_menue_create_multiplayer_button(
    game_mode_menue* mode_menu,
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
}

void game_mode_menue_create_header(game_mode_menue* mode_menu, lv_obj_t* parent){
    mode_menu->header = lv_label_create(mode_menu->div);
    lv_label_set_text_fmt(mode_menu->header, "SELECT GAME MODE");
    lv_obj_align(mode_menu->header, LV_ALIGN_TOP_MID, 0, 0);
}