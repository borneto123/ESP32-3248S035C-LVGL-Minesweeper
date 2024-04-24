#include <gui_timer_widget.hpp>
#include <Arduino.h>
#include <gui_grid_widget.hpp>

void gui_timer_widget_create(gui_timer_widget* timer, lv_obj_t* parent){
    gui_timer_widget_create_div(timer,parent);
    gui_timer_widget_create_label(timer,timer->div);
    timer->current_time = 0;
    timer->state = GUI_TIMER_WIDGET_STATE_STOPPED;
}

void gui_timer_widget_create_label(gui_timer_widget* timer, lv_obj_t* parent){
    timer->label = lv_label_create(parent);
    lv_obj_set_align(timer->label, LV_ALIGN_CENTER);
    lv_label_set_text_fmt(timer->label,"00:00");
}

void gui_timer_widget_start(gui_timer_widget* timer){
    timer->state = GUI_TIMER_WIDGET_STATE_RUNNING;
    timer->last_time = millis();
}
    
void gui_timer_widget_create_div(gui_timer_widget* timer, lv_obj_t* parent){
    timer->div = lv_obj_create(parent);
    lv_obj_remove_style_all(timer->div);
    gui_timer_widget_style_init(timer->div);
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


void gui_timer_widget_style_init(lv_obj_t* timer){
    static lv_style_t style;
    static int created = 0;

    if(!created){
    lv_style_init(&style);    
    lv_style_set_align(&style,LV_ALIGN_TOP_RIGHT);
    lv_style_set_text_color(&style, lv_palette_darken(LV_PALETTE_RED , 3));
    lv_style_set_bg_opa(&style, 255);
    lv_style_set_bg_color(&style, lv_color_black());
    lv_style_set_text_font(&style, &lv_font_montserrat_32);
    lv_style_set_width(&style, GUI_TIMER_WIDGET_WIDTH);
    lv_style_set_height(&style, GUI_TIMER_WIDGET_HEIGHT);
    }
    
    lv_obj_add_style(timer, &style, 0);
    created = 1;
}


void gui_timer_widget_delete(gui_timer_widget* timer){
    if(lv_obj_is_valid(timer->div))
    lv_obj_del(timer->div);
}