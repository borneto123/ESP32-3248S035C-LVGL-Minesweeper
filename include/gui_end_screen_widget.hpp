#ifndef _END_
#define _END_
#include <lvgl.h>
#include <logic_end_game_data.hpp>
#include <gui_menu.hpp>

/**
 * @brief Function that creates an end screen with the result
 * @param master pointer to game_widget
 * @param end_game_data result of the game
 */
void gui_end_screen_widget_create(gui_game_widget* master, logic_end_game_data end_game_data, int map_num);

/**
 * @brief Function that sets style of end screen(It is called multiple times to change bg color)
 * @param end_screen pointer to end_screen lv object
 * @param game_state state of the game
 */
void gui_end_screen_widget_set_style(lv_obj_t* end_screen, int game_state);

#endif