#ifndef _GAME_
#define _GAME_
#include <gui_grid_widget.hpp>
#include <gui_timer_widget.hpp>
#include <gui_mine_counter_widget.hpp>
#include <logic.hpp>
#include <logic_game_difficulty.hpp>
struct gui_game_widget{
    lv_obj_t* div;
    logic_data* master_grid_data;
    gui_grid_widget* master_grid;
    gui_timer_widget* master_timer;
    gui_mine_counter_widget* master_counter;
    bool started = false;
};

void gui_game_widget_create(gui_game_widget* master, logic_game_difficulty difficulty, lv_obj_t* parent);

void gui_game_widget_create_div(gui_game_widget* master, logic_game_difficulty difficulty, lv_obj_t* parent);


#endif