#ifndef _MENUE_
#define _MENUE_

#include <lvgl.h>
#include <gui_game_difficulty_button.hpp>

enum gui_difficulty_menue_constants{
    GUI_DIFFICULTY_MENUE_DEFAULT,
    GUI_DIFFICULTY_MENUE_CUSTOM,
};

struct gui_menue
{
    int page = GUI_DIFFICULTY_MENUE_DEFAULT;
    lv_obj_t* div;
    gui_game_difficulty_button* easy;
    gui_game_difficulty_button* medium;
    gui_game_difficulty_button* hard;
    gui_game_difficulty_button* custom;
    lv_obj_t* next_page_button;
    //Mine slider
    //Height slider
    //Width slider
};

void gui_menue_create(gui_menue* menue,gui_game_widget* master, lv_obj_t* parent);

void gui_menue_create_div(gui_menue* menue, lv_obj_t* parent);

void gui_menue_create_next_page_button(gui_menue* menue);

void gui_menue_next_page_button_cb(lv_event_cb_t* e);



#endif