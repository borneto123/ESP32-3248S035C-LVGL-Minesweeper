#include <gui_game_difficulty_button.hpp>
#include <Arduino.h>
#include <logic_wifi.hpp>

void gui_game_difficulty_button_create(gui_game_widget* master, gui_game_difficulty_button* difficulty,logic_game_difficulty* settings, const char* name, lv_color_t color_bg, lv_color_t color_text, lv_obj_t* parent){
    difficulty->settings = settings;
    difficulty->master = master;
    gui_game_difficulty_button_create_button(difficulty, name, color_bg, color_text, parent);
    
}

void gui_game_difficulty_button_create_button(gui_game_difficulty_button* difficulty, const char* name, lv_color_t color_bg, lv_color_t color_text, lv_obj_t* parent){

    difficulty->button = lv_btn_create(parent);
    
    lv_obj_t* label = lv_label_create(difficulty->button);
    lv_label_set_text_fmt(label, name);
    lv_obj_set_style_text_font(difficulty->button, &lv_font_montserrat_32, 0);
    lv_obj_set_style_bg_color(difficulty->button, color_bg, 0);
    lv_obj_set_style_text_color(difficulty->button, color_text, 0);
    lv_obj_add_event_cb(difficulty->button, gui_game_difficulty_button_cb, LV_EVENT_ALL, difficulty);
}

void gui_game_difficulty_button_cb(lv_event_t * e){
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t* obj = lv_event_get_target(e);
    gui_game_difficulty_button* difficulty = (gui_game_difficulty_button*)lv_event_get_user_data(e);
    if(code == LV_EVENT_CLICKED){
       // lv_obj_del(obj);
        if(difficulty->online_mode == 1 && wifi_device_type() == WIFI_DEVICE_MASTER){
            //Add online mode logic
            Serial.println("Sending data");
            difficulty->settings->seed = millis()%100;
            wifi_send_difficulty(*difficulty->settings);
            gui_game_widget_multiplayer(difficulty->master);
        }
        else if(difficulty->online_mode == 0){
            gui_game_widget_singleplayer(difficulty->master);
            Serial.println("Offline");
        }
        gui_game_widget_create(difficulty->master, *difficulty->settings, lv_scr_act());
    }       
}
void gui_game_difficulty_button_set_position(gui_game_difficulty_button* difficulty, int x, int y){

    lv_obj_set_pos(difficulty->button, x, y);

}

void gui_game_difficulty_button_show(gui_game_difficulty_button* difficulty){
    lv_obj_clear_flag(difficulty->button, LV_OBJ_FLAG_HIDDEN);
}

void gui_game_difficulty_button_hide(gui_game_difficulty_button* difficulty){
    lv_obj_add_flag(difficulty->button, LV_OBJ_FLAG_HIDDEN);
}

void gui_game_difficulty_singleplayer(gui_game_difficulty_button* difficulty){
    difficulty->online_mode = 0;
}
void gui_game_difficulty_multiplayer(gui_game_difficulty_button* difficulty){
    difficulty->online_mode = 1;
}