#include <gui_menue.hpp>
void gui_menu_create(gui_menu* menue,gui_game_widget* master, lv_obj_t* parent){
    
    gui_menue_create_div(menue, parent);
    gui_menu_waiting_create(menue, parent);
    menue->online_mode = -1;
    menue->easy = new gui_game_difficulty_button;
    menue->medium = new gui_game_difficulty_button;
    menue->hard = new gui_game_difficulty_button;
    menue->master = master;
    logic_game_difficulty* easy_data = new logic_game_difficulty;
    logic_game_difficulty* medium_data = new logic_game_difficulty;
    logic_game_difficulty* hard_data = new logic_game_difficulty;

    logic_game_difficulty_create(easy_data, 9, 9, 10,NULL);
    logic_game_difficulty_create(medium_data, 14, 14, 40,NULL);
    logic_game_difficulty_create(hard_data, 20, 20, 99,NULL);

    gui_game_difficulty_button_create(
        master,
        menue->easy, 
        easy_data, 
        "Easy", 
        lv_color_black(),
        lv_color_white(),
        lv_scr_act()
    );

    gui_game_difficulty_button_create(
        master,
        menue->medium, 
        medium_data, 
        "Medium", 
        lv_color_black(),
        lv_color_white(),
        lv_scr_act()
    );

    gui_game_difficulty_button_create(
        master,
        menue->hard, 
        hard_data, 
        "Hard", 
        lv_color_black(),
        lv_color_white(),
        lv_scr_act()
    );
    gui_game_difficulty_button_set_position(menue->easy, 110, 100);
    gui_game_difficulty_button_set_position(menue->medium, 80, 200);
    gui_game_difficulty_button_set_position(menue->hard, 110, 300);
}

void gui_menue_create_div(gui_menu* menue, lv_obj_t* parent){
    menue->div = lv_obj_create(parent);
    lv_obj_remove_style_all(menue->div);
    lv_obj_set_size(menue->div, 320, 480);   
}


void gui_menu_singleplayer(gui_menu* menu){
    menu->online_mode = 0;
    menu->master->online_mode = 0;
}
void gui_menu_multiplayer(gui_menu* menu){
    menu->online_mode = 1;
    menu->master->online_mode = 1;
    wifi_init(menu);
    Serial.println("Wifi initialized");
    if(wifi_device_type() == WIFI_DEVICE_SLAVE){
        gui_game_difficulty_button_hide(menu->easy);
        gui_game_difficulty_button_hide(menu->medium);
        gui_game_difficulty_button_hide(menu->hard);
        gui_menu_waiting_show(menu);

    }
    if(wifi_device_type() == WIFI_DEVICE_MASTER){
        gui_game_difficulty_multiplayer(menu->easy);
        gui_game_difficulty_multiplayer(menu->medium);
        gui_game_difficulty_multiplayer(menu->hard);
    }
}

void gui_menu_waiting_create(gui_menu* menue, lv_obj_t* parent){
    menue->waiting_label = lv_label_create(parent);
    lv_label_set_text(menue->waiting_label, "Waiting...");
    gui_menu_waiting_hide(menue);
}

void gui_menu_waiting_show(gui_menu* menu){
    lv_obj_clear_flag(menu->waiting_label, LV_OBJ_FLAG_HIDDEN);
}

void gui_menu_waiting_hide(gui_menu* menu){
    lv_obj_add_flag(menu->waiting_label, LV_OBJ_FLAG_HIDDEN);
}

void gui_menu_show(gui_menu* menu){
    lv_obj_clear_flag(menu->div, LV_OBJ_FLAG_HIDDEN);
}

void gui_menu_hide(gui_menu* menu){
    lv_obj_add_flag(menu->div, LV_OBJ_FLAG_HIDDEN);
}

void gui_menu_slave_receive_difficulty(wifi_data data){
    gui_game_widget_create(data.menu->master, data.receive.difficulty, lv_scr_act());
}