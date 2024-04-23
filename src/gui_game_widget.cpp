#include <gui_game_widget.hpp>
#include <Arduino.h>

void gui_game_widget_create(gui_game_widget* master, logic_game_difficulty difficulty, lv_obj_t* parent){
    if(!master->started){
    master->master_grid_data = new logic_data;
    master->master_grid = new gui_grid_widget;
    master->master_counter = new gui_mine_counter_widget;
    master->master_timer = new gui_timer_widget;
   // master->master_end_screen = new gui_end_screen_widget;
    
    
    }
    logic_create_logic_data(master->master_grid_data, difficulty.rows, difficulty.cols, difficulty.mines, difficulty.seed);
    Serial.println("Logic Data Created");
    gui_game_widget_create_div(master, difficulty, parent);
    Serial.println("Gui_game_widget_div");
    gui_grid_widget_create(master->master_grid, master->master_grid_data, master->div);
    Serial.println("Gui_game_widget");
    gui_timer_widget_create(master->master_timer, master->div);
    Serial.println("Gui_game_timer");
    gui_timer_widget_start(master->master_timer);
    gui_mine_counter_widget_create(master->master_counter, master->master_grid_data, master->div);

    gui_game_widget_create_button(master, master->div);

    master->started = true;
    master->created = true;

    logic_data_set_game_widget(master->master_grid_data, master);

    
}

void gui_game_widget_create_div(gui_game_widget* master, logic_game_difficulty difficulty, lv_obj_t* parent){
    master->div = lv_obj_create(parent);


    lv_obj_set_size(master->div, 320, 480);
    lv_obj_set_style_border_width(master->div, 0, 0);
    lv_obj_set_style_radius(master->div, 0, 0);
    lv_obj_set_style_bg_color(master->div, lv_color_white(), 0);
    lv_obj_set_style_pad_all(master->div, 0 ,0);

}
void gui_game_widget_delete(gui_game_widget* master){
    Serial.println("\nBrisem sve iz game widget");
    gui_timer_widget_delete(master->master_timer);
    gui_mine_counter_widget_delete(master->master_counter);
    gui_grid_widget_delete(master->master_grid);
    logic_data_delete(master->master_grid_data);
    delete master->master_timer;
    delete master->master_counter;
    delete master->master_grid;
    delete master->master_grid_data;

  //  delete master->master_end_screen;
    lv_obj_del(master->div);
    Serial.println("\nOrisano sve iz game widget");
    master->started = false;
    

}

void gui_game_widget_create_button(
    gui_game_widget* master,
    lv_obj_t* parent
){
    master->back_button = lv_btn_create(parent);
    lv_obj_t* label = lv_label_create(master->back_button);
    lv_label_set_text(label, LV_SYMBOL_CLOSE);
    lv_obj_align(master->back_button, LV_ALIGN_TOP_MID,0,0);
    lv_obj_set_style_bg_color(master->back_button, lv_color_make(196, 40, 35), 0);
    lv_obj_add_event_cb(master->back_button, gui_game_widget_button_cb, LV_EVENT_ALL, master);

}

void gui_game_widget_button_cb(lv_event_t* e){
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t* obj = lv_event_get_target(e);
    gui_game_widget* master = (gui_game_widget*)lv_event_get_user_data(e); 
    if(code == LV_EVENT_CLICKED){
        //ESP.restart();
        gui_game_widget_delete(master);
        
    }
}

void gui_game_widget_singleplayer(gui_game_widget* master){
    master->online_mode = 0;
}

void gui_game_widget_multiplayer(gui_game_widget* master){
    master->online_mode = 1;
}