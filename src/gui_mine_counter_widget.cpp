#include <gui_mine_counter_widget.hpp>

void gui_mine_counter_widget_create(gui_mine_counter_widget* counter, logic_data* game_data, lv_obj_t* parent){
    gui_mine_counter_widget_create_div(counter, parent);
    gui_mine_counter_widget_create_label(counter, counter->div);
    gui_mine_counter_style_init();
}


void gui_mine_counter_widget_create_label(gui_mine_counter_widget* counter, lv_obj_t* parent){
    counter->label = lv_label_create(parent);
    lv_obj_set_align(counter->label, LV_ALIGN_CENTER);
    lv_label_set_text_fmt(counter->label,"000");
}

void gui_mine_counter_widget_create_div(gui_mine_counter_widget* counter, lv_obj_t* parent){
    counter->div = lv_obj_create(parent);
    lv_obj_remove_style_all(counter->div);
    lv_obj_add_style(counter->div, &gui_style_mine_counter_widget, 0);
}

void gui_mine_counter_widget_refresh(gui_mine_counter_widget* counter, logic_data* game_data){
    int display = game_data->mines_remaining;
    if(display < 0) display = 0;
    lv_label_set_text_fmt(counter->label, "%03d",display);
}

void gui_mine_counter_style_init(){
    lv_style_init(&gui_style_mine_counter_widget);
    lv_style_set_align(&gui_style_mine_counter_widget,LV_ALIGN_TOP_LEFT);
    lv_style_set_text_color(&gui_style_mine_counter_widget, lv_palette_darken(LV_PALETTE_RED , 3));
    lv_style_set_bg_opa(&gui_style_mine_counter_widget, 255);
    lv_style_set_bg_color(&gui_style_mine_counter_widget, lv_color_black());
    lv_style_set_text_font(&gui_style_mine_counter_widget, &lv_font_montserrat_32);
    lv_style_set_width(&gui_style_mine_counter_widget, GUI_MINE_COUNTER_WIDGET_WIDTH);
    lv_style_set_height(&gui_style_mine_counter_widget, GUI_MINE_COUNTER_HEIGHT);
}