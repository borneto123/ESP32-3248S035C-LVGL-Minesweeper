#include <gui_end_screen_widget.hpp>
#include <logic.hpp>
#include <Arduino.h>
void gui_end_screen_widget_create(gui_game_widget* master, logic_end_game_data end_game_data, int map_num){
    char header[50];
    char message[90];
    if(end_game_data.state == LOGIC_DATA_STATE_LOST){
        sprintf(header, "YOU LOST");
    }
    else if(end_game_data.state == LOGIC_DATA_STATE_WON){
        sprintf(header, "YOU WON");
    }
    else if(end_game_data.state == LOGIC_DATA_STATE_TIE){
        sprintf(header, "GAME IS TIED");
    }
    else if(end_game_data.state == LOGIC_DATA_STATE_WAITING){
        sprintf(header, "WAITING FOR \nOTHER PLAYER");
    }
    else{
        sprintf(header, "ERROR");
    }
    if(map_num !=1) {
     sprintf(
            message,
            "Score: %d\nTime:%02lu:%02lu",
            end_game_data.score,
            (end_game_data.time/1000)/60,
            (end_game_data.time/1000)%60
            );
    }
    else if(map_num == 1 && end_game_data.state == LOGIC_DATA_STATE_WAITING){
        sprintf(message, "Your score:%d",end_game_data.score);
    }
    else{
        sprintf(message, "Your score:%d\nRival score:%d",end_game_data.score, end_game_data.packet_score);
    }

    if(!lv_obj_is_valid(master->result)){
        master->result = lv_label_create(master->div);
    }
    
    lv_label_set_text_fmt(master->result, "%s\n%s",header,message);
    gui_end_screen_widget_set_style(master->result, end_game_data.state);
}

void gui_end_screen_widget_set_style(lv_obj_t* end_screen, int game_state){
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
    lv_style_set_align(&style, LV_ALIGN_CENTER);
    
    }
    created = 1;
    if(game_state == LOGIC_DATA_STATE_WON) {
        lv_style_set_bg_color(&style, lv_color_make(112, 151, 117));    
    }
    else if(game_state == LOGIC_DATA_STATE_LOST) {
        lv_style_set_bg_color(&style, lv_color_make(231, 115, 113));
    }
    else if(game_state == LOGIC_DATA_STATE_WAITING) {
        lv_style_set_bg_color(&style, lv_color_make(240, 200, 8));
    }
    else{
        lv_style_set_bg_color(&style, lv_color_white());
    }
    lv_obj_add_style(end_screen, &style, 0);
}


