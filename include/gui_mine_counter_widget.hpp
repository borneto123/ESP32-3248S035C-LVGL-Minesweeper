#ifndef _GUI_MINE_COUNTER_WIDGET
#define _GUI_MINE_COUNTER_WIDGET
#include <lvgl.h>
#include <logic.hpp>

struct logic_data;

enum gui_mine_counter_widget_contant{
    GUI_MINE_COUNTER_WIDGET_WIDTH = 100,
    GUI_MINE_COUNTER_HEIGHT = 50,
};
/**
 * This struct stores information about mine counter:
 * - `div` label parent
 * - `label` label that displays the number of remaining mines
 */
struct gui_mine_counter_widget{
    lv_obj_t* div;
    lv_obj_t* label;
};

/**
 * @brief Function that creates mine counter widget
 * @param counter pointer to gui_mine_counter_widget
 * @param game_data pointer to logic_data
 * @param parent pointer to parent
 */
void gui_mine_counter_widget_create(gui_mine_counter_widget* counter, logic_data* game_data, lv_obj_t* parent);

/**
 * @brief Function that creates div for mine counter
 * @param counter pointer to gui_mine_counter_widget
 * @param parent pointer to parent
 */
void gui_mine_counter_widget_create_div(gui_mine_counter_widget* counter, lv_obj_t* parent);

/**
 * @brief Function that creates the label for mine counter
 * @param counter pointer to gui_mine_counter_widget
 * @param parent pointer to parent
 */
void gui_mine_counter_widget_create_label(gui_mine_counter_widget* counter, lv_obj_t* parent);

/**
 * @brief Function that refreshes mine counter
 * @param counter pointer to gui_mine_counter_widget
 * @param game_data pointer to logic_data
 */
void gui_mine_counter_widget_refresh(gui_mine_counter_widget* counter,  logic_data* game_data);

/**
 * @brief Function that adds styles to mine counter
 * @param counter pointer to counter object
 */
void gui_mine_counter_style_init(lv_obj_t* counter);

/**
 * @brief Function that deletes mine counter and frees memory
 * @param counter 
 */
void gui_mine_counter_widget_delete(gui_mine_counter_widget* counter);
#endif