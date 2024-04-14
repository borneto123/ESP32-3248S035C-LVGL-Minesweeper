#ifndef _GAME_MODE_
#define _GAME_MODE_
#include <lvgl.h>
#include <gui_menue.hpp>
struct game_mode_menue{
    lv_obj_t* div;
    lv_obj_t* header;
    lv_obj_t* singleplayer_button;
    lv_obj_t* multiplayer_button;
    gui_menue* difficulty_menue;
};


void game_mode_menue_create(
    game_mode_menue* mode_menu,
    lv_obj_t* parent,
    gui_menue* difficulty_menue
);

void game_mode_menue_create_div(game_mode_menue* mode_menu, lv_obj_t* parent);

void game_mode_menue_create_singleplayer_button(
    game_mode_menue* mode_menu,
    lv_obj_t* parent,
    lv_color_t text_color,
    lv_color_t bg_color
);

void game_mode_menue_create_multiplayer_button(
    game_mode_menue* mode_menu,
    lv_obj_t* parent,
    lv_color_t text_color,
    lv_color_t bg_color
);

void game_mode_menue_create_header(game_mode_menue* mode_menu, lv_obj_t* parent);

void game_mode_menue_singleplayer_button_cb(lv_event_t* e);

void game_mode_menue_multiplayer_button_cb(lv_event_t* e);

#endif