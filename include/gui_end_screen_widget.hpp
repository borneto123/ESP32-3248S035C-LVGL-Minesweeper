#ifndef _END_
#define _END_
#include <lvgl.h>

struct gui_end_screen_widget
{
    //lv_obj_t* parent;
    lv_obj_t* end_screen;
};

void gui_end_screen_widget_create(gui_end_screen_widget* screen, int state, int seed);





#endif