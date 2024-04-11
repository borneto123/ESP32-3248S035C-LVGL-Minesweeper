#include <gui_menue.hpp>

void gui_menue_create(gui_menue* menue,gui_game_widget* master, lv_obj_t* parent){
    
    gui_menue_create_div(menue, parent);

    menue->easy = new gui_game_difficulty_button;
    menue->medium = new gui_game_difficulty_button;
    menue->hard = new gui_game_difficulty_button;

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

void gui_menue_create_div(gui_menue* menue, lv_obj_t* parent){
    menue->div = lv_obj_create(parent);
    lv_obj_remove_style_all(menue->div);
    lv_obj_set_size(menue->div, 320, 480);   
}