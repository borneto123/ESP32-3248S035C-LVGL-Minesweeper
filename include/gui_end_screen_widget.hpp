#ifndef _END_
#define _END_
#include <lvgl.h>
#include <logic_end_game_data.hpp>
#include <gui_menue.hpp>
struct gui_end_screen_widget
{
    lv_obj_t* end_screen;
    
};



void gui_end_screen_widget_create(gui_game_widget* master, logic_end_game_data end_game_data);

void gui_end_screen_widget_set_style(lv_obj_t* end_screen, int game_state);

void test_gui_end_screen_widget_create(gui_game_widget* master, logic_end_game_data end_game_data);

// Deleteing text
void gui_end_screen_widget_delete(gui_end_screen_widget* screen);






#endif