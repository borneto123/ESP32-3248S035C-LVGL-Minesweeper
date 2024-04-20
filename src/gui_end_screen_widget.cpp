#include <gui_end_screen_widget.hpp>
#include <logic.hpp>
#include <Arduino.h>
void gui_end_screen_widget_create(gui_game_widget* master, logic_end_game_data end_game_data){
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
     sprintf(
            message,
            "Score: %d\nTime:%02lu:%02lu",
            end_game_data.score, (end_game_data.time/1000)/60,(end_game_data.time/1000)%60);
    if(lv_obj_is_valid(master->result)){
        Serial.println("\nDeleting object");
        lv_obj_del(master->result);
    }
    master->result = lv_label_create(master->div);
    lv_obj_set_style_align(master->result, LV_ALIGN_CENTER, 0);
    lv_label_set_text_fmt(master->result, "%s\n%s",header,message);
    gui_end_screen_widget_set_style(master->result, end_game_data.state);
}

void gui_end_screen_widget_set_style(lv_obj_t* end_screen, int game_state){
    lv_obj_set_style_bg_opa(end_screen, 255, 0);
    lv_obj_set_style_text_color(end_screen, lv_color_black(), 0);
    lv_obj_set_style_text_font(end_screen, &lv_font_montserrat_32, 0);
    lv_obj_set_style_border_color(end_screen, lv_color_black(), 0);
    lv_obj_set_style_border_width(end_screen, 7, 0);
    lv_obj_set_style_text_align(end_screen, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_style_pad_all(end_screen, 15, 0);

    if(game_state == LOGIC_DATA_STATE_WON) {
        lv_obj_set_style_bg_color(end_screen, lv_color_make(112, 151, 117),0);    
    }
    else if(game_state == LOGIC_DATA_STATE_LOST) {
        lv_obj_set_style_bg_color(end_screen, lv_color_make(231, 115, 113),0);
    }
    else if(game_state == LOGIC_DATA_STATE_WAITING) {
        lv_obj_set_style_bg_color(end_screen, lv_color_make(240, 200, 8),0);
    }
    else{
        lv_obj_set_style_bg_color(end_screen, lv_color_white() ,0);
    }
    lv_event_send(end_screen, LV_EVENT_VALUE_CHANGED, NULL);
}

void test_gui_end_screen_widget_create(gui_game_widget* master, logic_end_game_data end_game_data){
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
        sprintf(header, "WAITING FOR OTHER PLAYER");
    }
    else{
        sprintf(header, "ERROR");
    } 
     sprintf(
            message,
            "Score: %d\nTime:%02lu:%02lu",
            end_game_data.score, (end_game_data.time/1000)/60,(end_game_data.time/1000)%60);
    if(lv_obj_is_valid(master->result)){

        lv_obj_del(master->result);
    }
    master->result = lv_label_create(master->div);
    lv_obj_set_style_align(master->result, LV_ALIGN_CENTER, 0);
    lv_label_set_text_fmt(master->result, "\n%s\n%s",header,message);
}


void gui_end_screen_widget_delete(gui_end_screen_widget* screen){
    
    if(lv_obj_is_valid(screen->end_screen)){
        Serial.println("\nClosing end screen");
        lv_msgbox_close(screen->end_screen);
        lv_obj_del(screen->end_screen);
    }
    else{
        Serial.println("\nNot closing end screen");
    }
}