#include <gui_game_widget.hpp>
#include <Arduino.h>

void gui_game_widget_create(gui_game_widget* master, logic_game_difficulty difficulty, lv_obj_t* parent){
    master->master_grid_data = new logic_data;
    master->master_grid = new gui_grid_widget;
    master->master_counter = new gui_mine_counter_widget;
    master->master_timer = new gui_timer_widget;

    logic_create_logic_data(master->master_grid_data, difficulty.rows, difficulty.cols, difficulty.mines);
    Serial.println("Logic Data Created");
    gui_game_widget_create_div(master, difficulty, parent);
    Serial.println("Gui_game_widget_div");
    gui_grid_widget_create(master->master_grid, master->master_grid_data, master->div);
    Serial.println("Gui_game_widget");
    gui_timer_widget_create(master->master_timer, master->div);
    Serial.println("Gui_game_timer");
    gui_timer_widget_start(master->master_timer);
    gui_mine_counter_widget_create(master->master_counter, master->master_grid_data, master->div);

    master->started = true;
}

void gui_game_widget_create_div(gui_game_widget* master, logic_game_difficulty difficulty, lv_obj_t* parent){
    master->div = lv_obj_create(parent);
    lv_obj_remove_style_all(master->div);
    lv_obj_set_size(master->div, 320, 480);
}
