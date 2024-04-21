#include <gui_mine_counter_widget.hpp>

void gui_mine_counter_widget_create(gui_mine_counter_widget* counter, logic_data* game_data, lv_obj_t* parent){
    gui_mine_counter_widget_create_div(counter, parent);
    gui_mine_counter_widget_create_label(counter, counter->div);
}


void gui_mine_counter_widget_create_label(gui_mine_counter_widget* counter, lv_obj_t* parent){
    counter->label = lv_label_create(parent);
    lv_obj_set_align(counter->label, LV_ALIGN_CENTER);
    lv_label_set_text_fmt(counter->label,"000");
}

void gui_mine_counter_widget_create_div(gui_mine_counter_widget* counter, lv_obj_t* parent){
    counter->div = lv_obj_create(parent);
    lv_obj_remove_style_all(counter->div);
    gui_mine_counter_style_init(counter->div);
}

void gui_mine_counter_widget_refresh(gui_mine_counter_widget* counter, logic_data* game_data){
    int display = game_data->mines_remaining;
    if(display < 0) display = 0;
    lv_label_set_text_fmt(counter->label, "%03d",display);
}

void gui_mine_counter_style_init(lv_obj_t* counter){
    static lv_style_t style;
    static int created = 0;

    if(!created){
    lv_style_init(&style);
    lv_style_set_align(&style,LV_ALIGN_TOP_LEFT);
    lv_style_set_text_color(&style, lv_palette_darken(LV_PALETTE_RED , 3));
    lv_style_set_bg_opa(&style, 255);
    lv_style_set_bg_color(&style, lv_color_black());
    lv_style_set_text_font(&style, &lv_font_montserrat_32);
    lv_style_set_width(&style, GUI_MINE_COUNTER_WIDGET_WIDTH);
    lv_style_set_height(&style, GUI_MINE_COUNTER_HEIGHT);
    }
    lv_obj_add_style(counter, &style, 0);
    created = 1;
}

void gui_mine_counter_widget_delete(gui_mine_counter_widget* counter){
    lv_obj_del(counter->div);
}