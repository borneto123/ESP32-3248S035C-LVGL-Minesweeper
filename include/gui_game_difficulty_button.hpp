#ifndef _DIFFICULTY_
#define _DIFFICULTY_
#include <lvgl.h>
#include <logic_game_difficulty.hpp>
#include <gui_game_widget.hpp>

struct gui_game_difficulty_button{

    logic_game_difficulty* settings;
    gui_game_widget* master;
    lv_obj_t* button;
    int online_mode;
};

void gui_game_difficulty_button_create(
    gui_game_widget* master, 
    gui_game_difficulty_button* difficulty,
    logic_game_difficulty* settings, 
    const char* name,
    lv_color_t color_bg,
    lv_color_t color_text,
    lv_obj_t* parent
);

void gui_game_difficulty_button_create_button(
    gui_game_difficulty_button* difficulty, 
    const char* name, 
    lv_color_t color_bg, 
    lv_color_t color_text,
    lv_obj_t* parent
);

void gui_game_difficulty_button_cb(lv_event_t * e);

void gui_game_difficulty_button_set_position(gui_game_difficulty_button* difficulty, int x, int y);

void gui_game_difficulty_button_show(gui_game_difficulty_button* difficulty);

void gui_game_difficulty_button_hide(gui_game_difficulty_button* difficulty);


void gui_game_difficulty_singleplayer(gui_game_difficulty_button* difficulty);
void gui_game_difficulty_multiplayer(gui_game_difficulty_button* difficulty);
//Add function to delete parent 


#endif