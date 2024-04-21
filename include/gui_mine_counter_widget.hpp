#ifndef _GUI_MINE_COUNTER_WIDGET
#define _GUI_MINE_COUNTER_WIDGET
#include <lvgl.h>
#include <logic.hpp>

struct logic_data;

enum gui_mine_counter_widget_contant{
    GUI_MINE_COUNTER_WIDGET_WIDTH = 100,
    GUI_MINE_COUNTER_HEIGHT = 50,
};

struct gui_mine_counter_widget{
    lv_obj_t* div;
    lv_obj_t* label;
};

void gui_mine_counter_widget_create(gui_mine_counter_widget* counter, logic_data* game_data, lv_obj_t* parent);

void gui_mine_counter_widget_create_div(gui_mine_counter_widget* counter, lv_obj_t* parent);

void gui_mine_counter_widget_create_label(gui_mine_counter_widget* counter, lv_obj_t* parent);

void gui_mine_counter_widget_refresh(gui_mine_counter_widget* counter,  logic_data* game_data);

void gui_mine_counter_style_init(lv_obj_t* counter);

void gui_mine_counter_widget_delete(gui_mine_counter_widget* counter);
#endif