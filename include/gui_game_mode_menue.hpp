#ifndef _GAME_MODE_
#define _GAME_MODE_
#include <lvgl.h>
#include <gui_menue.hpp>

struct gui_menu;

struct gui_game_mode_menue{
    lv_obj_t* div;
    lv_obj_t* header;
    lv_obj_t* singleplayer_button;
    lv_obj_t* multiplayer_button;
    gui_menu* difficulty_menue;
};


void gui_game_mode_menue_create(
    gui_game_mode_menue* mode_menu,
    lv_obj_t* parent,
    gui_menu* difficulty_menue
);

void gui_game_mode_menue_create_div(gui_game_mode_menue* mode_menu, lv_obj_t* parent);

void gui_game_mode_menue_create_singleplayer_button(
    gui_game_mode_menue* mode_menu,
    lv_obj_t* parent,
    lv_color_t text_color,
    lv_color_t bg_color
);

void gui_game_mode_menue_create_multiplayer_button(
    gui_game_mode_menue* mode_menu,
    lv_obj_t* parent,
    lv_color_t text_color,
    lv_color_t bg_color
);

void gui_game_mode_menue_create_header(gui_game_mode_menue* mode_menu, lv_obj_t* parent);

void gui_game_mode_menue_singleplayer_button_cb(lv_event_t* e);

void gui_game_mode_menue_multiplayer_button_cb(lv_event_t* e);

void gui_game_mode_menue_show(gui_game_mode_menue* mode_menu);

void gui_game_mode_menue_hide(gui_game_mode_menue* mode_menu);

#endif