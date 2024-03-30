#include <gui_timer_widget.hpp>
#include <Arduino.h>
void gui_timer_widget_create(gui_timer_widget* timer, lv_obj_t* parent){
    gui_timer_widget_create_label(timer,parent);
    timer->current_time = 0;
    timer->state = GUI_TIMER_WIDGET_STATE_STOPPED;
}

void gui_timer_widget_create_label(gui_timer_widget* timer, lv_obj_t* parent){
    timer->label = lv_label_create(parent);
    lv_label_set_text_fmt(timer->label,"00:00");
}

void gui_timer_widget_start(gui_timer_widget* timer){
    timer->state = GUI_TIMER_WIDGET_STATE_RUNNING;
    timer->last_time = millis();
}

void gui_timer_widget_stop(gui_timer_widget* timer){
    timer->state = GUI_TIMER_WIDGET_STATE_STOPPED;
    gui_timer_widget_refresh(timer);
}

void gui_timer_widget_refresh(gui_timer_widget* timer){
    if(timer->state == GUI_TIMER_WIDGET_STATE_RUNNING){
        timer->current_time += millis() - timer->last_time;
        timer->last_time = millis();
        lv_label_set_text_fmt(timer->label,"%02lu:%02lu",(timer->current_time/1000)/60,(timer->current_time/1000)%60);
    }
}