#include <gui_end_screen_widget.hpp>
#include <logic.hpp>
#include <Arduino.h>
void gui_end_screen_widget_create(gui_end_screen_widget* screen, int state, int seed){
    
    if(state == LOGIC_DATA_STATE_LOST){
    char message[70];
    sprintf(message, "You clicked on the mine\nSeed:%d",seed);
    screen->end_screen = lv_msgbox_create(NULL, "YOU LOST!",message, NULL, true);
    lv_obj_set_style_align(screen->end_screen, LV_ALIGN_CENTER, 0);
    }
    if(state == LOGIC_DATA_STATE_WON){
    char message[70];
    sprintf(message, "You cleared all of the mines\nSeed:%d",seed);
    screen->end_screen = lv_msgbox_create(NULL, "YOU WON!",message, NULL, true);
    lv_obj_set_style_align(screen->end_screen, LV_ALIGN_CENTER, 0);
    }
}