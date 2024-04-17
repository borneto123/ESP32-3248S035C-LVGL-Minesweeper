#include <gui_end_screen_widget.hpp>
#include <logic.hpp>
#include <Arduino.h>
void gui_end_screen_widget_create(gui_end_screen_widget* screen, logic_end_game_data end_game_data){
    char header[30];
    char message[70];
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
    sprintf(
            message,
            "Score: %d\nTime:%02lu:%02lu",
            end_game_data.score, (end_game_data.time/1000)/60,(end_game_data.time/1000)%60);
    screen->end_screen = lv_msgbox_create(NULL,header,message, NULL, true);
    lv_obj_set_style_align(screen->end_screen, LV_ALIGN_CENTER, 0);
    
}