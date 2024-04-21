#ifndef _GUI_TIMER_WIDGET
#define _GUI_TIMER_WIDGET
#include <lvgl.h>

enum gui_timer_widget_constant{
    GUI_TIMER_WIDGET_STATE_STOPPED = 0,
    GUI_TIMER_WIDGET_STATE_RUNNING = 1,
    GUI_TIMER_WIDGET_WIDTH = 100,
    GUI_TIMER_WIDGET_HEIGHT = 50,
    GUI_TIMER_WIDGET_FONT_SIZE,
};

/**
 * Struct that stores pointer for timer object and time in milis:
 * - `div` pointer to parent of label
 * - `label` pointer to label
 * - `current_time` time passed ind milliseconds
 * - `last_time` time when timer was last refreshed
 * - `state` time passed ind milliseconds
 */
struct gui_timer_widget{
    lv_obj_t* div;
    lv_obj_t* label;
    unsigned long int current_time;
    unsigned long int last_time;
    bool state;

};

/**
 * @brief Function that creates timer widget
 * 
 * @param timer pointer to gui_timer_widget
 * @param parent pointer to parent of label
 */
void gui_timer_widget_create(gui_timer_widget* timer, lv_obj_t* parent);

/**
 * @brief Function that creates label object inside gui_timer_widget_struct
 * 
 * @param timer pointer to gui_timer_widget
 * @param parent pointer to parent of label
 */
void gui_timer_widget_create_label(gui_timer_widget* timer, lv_obj_t* parent);

/**
 * @brief Function that creates parent of label widget[TO-DO]
 * 
 * @param timer pointer to gui_timer_widget
 * @param parent pointer to parent of label
 */
void gui_timer_widget_create_div(gui_timer_widget* timer, lv_obj_t* parent);

/**
 * @brief Function that starts counting time for timer widget
 * 
 * @param timer pointer to gui_timer_widget
 */
void gui_timer_widget_start(gui_timer_widget* timer);

/**
 * @brief Function that stops counting time for timer widget
 * 
 * @param timer pointer to gui_timer_widget
 */
void gui_timer_widget_stop(gui_timer_widget* timer);

/**
 * @brief Function that refreshes label text
 * 
 * @param timer pointer to gui_timer_widget
 */
void gui_timer_widget_refresh(gui_timer_widget* timer);



/**
 * @brief Fucntion that initializes styles for timer widget 
 * 
 */
void gui_timer_widget_style_init(lv_obj_t* timer);


void gui_timer_widget_delete(gui_timer_widget* timer);

#endif