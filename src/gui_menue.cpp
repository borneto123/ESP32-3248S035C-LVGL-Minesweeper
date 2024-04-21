#include <gui_menue.hpp>
void gui_menu_create(gui_menu* menue,gui_game_widget* master, lv_obj_t* parent){
    
    gui_menue_create_div(menue, parent);
    gui_menu_waiting_create(menue, parent);
    gui_menue_create_back_button(menue, parent); 
    menue->online_mode = -1;
    menue->easy = new gui_game_difficulty_button;
    menue->medium = new gui_game_difficulty_button;
    menue->hard = new gui_game_difficulty_button;
    menue->master = master;
    logic_game_difficulty* easy_data = new logic_game_difficulty;
    logic_game_difficulty* medium_data = new logic_game_difficulty;
    logic_game_difficulty* hard_data = new logic_game_difficulty;

    logic_game_difficulty_create(easy_data, 9, 9, 10, NULL);
    logic_game_difficulty_create(medium_data, 14, 14, 40, NULL);
    logic_game_difficulty_create(hard_data, 20, 20, 99, NULL);

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
    Serial.println("Singleplayer started");
    menu->online_mode = 0;
    gui_game_difficulty_singleplayer(menu->easy);
    gui_game_difficulty_singleplayer(menu->medium);
    gui_game_difficulty_singleplayer(menu->hard);
    gui_menue_item_show(menu->easy->button);
    gui_menue_item_show(menu->medium->button);
    gui_menue_item_show(menu->hard->button);
    gui_menue_item_hide(menu->waiting_label);
    gui_menue_item_show(menu->back_button);
}
void gui_menu_multiplayer(gui_menu* menu){
    Serial.println("Multiplayer started");
    menu->online_mode = 1;
    menu->master->online_mode = 1;

    wifi_init(menu);
    Serial.println("Wifi initialized");
    if(wifi_device_type() == WIFI_DEVICE_SLAVE){
        gui_menue_item_hide(menu->easy->button);
        gui_menue_item_hide(menu->medium->button);
        gui_menue_item_hide(menu->hard->button);

        gui_menue_item_show(menu->waiting_label);
        gui_menue_item_show(menu->back_button);
        

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
    gui_menue_item_hide(menue->waiting_label);
   gui_menu_waiting_style_init(menue->waiting_label);
}

void gui_menu_waiting_style_init(lv_obj_t* waiting_label){

    static lv_style_t style;
    static int created = 0;
    if(!created){
    lv_style_init(&style);    
    lv_style_set_bg_opa(&style, 255);
    lv_style_set_text_color(&style, lv_color_black());
    lv_style_set_text_font(&style, &lv_font_montserrat_32);
    lv_style_set_border_color(&style, lv_color_black());
    lv_style_set_border_width(&style, 7);
    lv_style_set_text_align(&style, LV_TEXT_ALIGN_CENTER);
    lv_style_set_pad_all(&style, 15);
    lv_style_set_bg_color(&style, lv_color_make(240, 200, 8));
    lv_style_set_align(&style, LV_ALIGN_CENTER);
}
    lv_obj_add_style(waiting_label, &style, 0);
    created = 1;
}

void gui_menue_item_show(lv_obj_t* object){
    lv_obj_clear_flag(object, LV_OBJ_FLAG_HIDDEN);
}
void gui_menue_item_hide(lv_obj_t* object){
    lv_obj_add_flag(object, LV_OBJ_FLAG_HIDDEN);
}

void gui_menue_create_back_button(gui_menu* menu, lv_obj_t* parent){
    menu->back_button = lv_btn_create(parent);
    lv_obj_t* label = lv_label_create(menu->back_button);

    static lv_style_t style;
    static int created = 0;
    lv_label_set_text(label, "Back");
    if(!created){
    lv_style_init(&style);
    lv_style_set_text_color(&style, lv_color_black());
    lv_style_set_text_font(&style, &lv_font_montserrat_32);
    lv_style_set_bg_color(&style, lv_color_make(231, 115, 113));
    lv_style_set_align(&style, LV_ALIGN_TOP_LEFT);
    lv_obj_add_style(menu->back_button, &style, 0);
    }
   // gui_menue_item_hide(menu->back_button);
   lv_obj_add_event_cb(menu->back_button, gui_menue_back_button_cb, LV_EVENT_ALL, menu);
   created = 1;
}

void gui_menue_back_button_cb(lv_event_t * e){
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t* obj = lv_event_get_target(e);
    gui_menu* menu = (gui_menu*)lv_event_get_user_data(e);
    if(code == LV_EVENT_CLICKED){
        gui_game_mode_menue_show(menu->mode_menu);
    }
}


void gui_menu_slave_receive_difficulty(wifi_data data){
    Serial.printf("First: %d",data.menu->first);
    if(data.menu->first == 0)
    gui_game_widget_delete(data.menu->master);
    gui_game_widget_create(data.menu->master, data.receive.difficulty, lv_scr_act());
    data.menu->first = 1;
}