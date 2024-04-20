#ifndef _END_
#define _END_
#include <lvgl.h>
#include <logic_end_game_data.hpp>
struct gui_end_screen_widget
{
    //lv_obj_t* parent;
    lv_obj_t* end_screen;
};



void gui_end_screen_widget_create(gui_end_screen_widget* screen, logic_end_game_data end_game_data);

void gui_end_screen_widget_delete(gui_end_screen_widget* screen);






#endif