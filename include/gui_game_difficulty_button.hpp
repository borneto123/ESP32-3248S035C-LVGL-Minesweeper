#ifndef _DIFFICULTY_
#define _DIFFICULTY_
#include <lvgl.h>
#include <logic_game_difficulty.hpp>
#include <gui_game_widget.hpp>

struct gui_game_widget;
struct gui_game_difficulty_button;
struct logic_game_difficulty;

/**
 * This struct stores information about a difficulty button):
 * - `settings` pointer to logic_game_difficulty
 * - `master` pointer to gui_game_widget
 * - `button` pointer to lv_obj_t 
 * - `online_mode` `0` Singleplayer `1` Multiplayer
 */
struct gui_game_difficulty_button {
    logic_game_difficulty* settings;
    gui_game_widget* master;
    lv_obj_t* button;
    int online_mode;
    int multiplayer_map_num;
};

/**
 * @brief Function that creates game_difficulty_button
 * @param master pointer to gui_game_widget
 * @param difficulty pointer to gui_game_difficulty_button
 * @param settings pointer to logic_game_difficulty
 * @param name text that will be displayed on the button
 * @param color_bg background color 
 * @param color_text text color
 * @param parent pointer to the parent of the button
 */
void gui_game_difficulty_button_create(
    gui_game_widget* master, 
    gui_game_difficulty_button* difficulty,
    logic_game_difficulty* settings, 
    const char* name,
    lv_color_t color_bg,
    lv_color_t color_text,
    lv_obj_t* parent
);

/**
 * @brief Function that creates lv object button for difficulty button
 * @param difficulty pointer to gui_game_difficulty_button
 * @param name text that will be displayed on the button
 * @param color_bg background color 
 * @param color_text text color
 * @param parent pointer to the parent of the button
 */
void gui_game_difficulty_button_create_button(
    gui_game_difficulty_button* difficulty, 
    const char* name, 
    lv_color_t color_bg, 
    lv_color_t color_text,
    lv_obj_t* parent
);

/**
 * Callback function for pressing the difficulty button
 * - `Singleplayer` spawns gui_game_widget 
 * - `Multiplayer` if the device is master difficulty will be sent to the slave
 * 
 */
void gui_game_difficulty_button_cb(lv_event_t * e);


/**
 * @brief Function that sets the position of the difficulty button
 * @param difficulty pointer to gui_game_difficulty_button
 * @param x x coordinates 
 * @param y y coordinates
 */
void gui_game_difficulty_button_set_position(gui_game_difficulty_button* difficulty, int x, int y);

/**
 * @brief Function that makes button visible
 * @param difficulty pointer to gui_game_difficulty_button
 */
void gui_game_difficulty_button_show(gui_game_difficulty_button* difficulty);

/**
 * @brief Function that makes button invisible
 * @param difficulty pointer to gui_game_difficulty_button
 */
void gui_game_difficulty_button_hide(gui_game_difficulty_button* difficulty);

/**
 * @brief Function that sets online_mode of game difficulty button to `0`
 * @param difficulty pointer to gui_game_difficulty_button
 */
void gui_game_difficulty_singleplayer(gui_game_difficulty_button* difficulty);


/**
 * @brief Function that sets online_mode of game difficulty button to `1`
 * @param difficulty pointer to gui_game_difficulty_button
 */
void gui_game_difficulty_multiplayer(gui_game_difficulty_button* difficulty, int map_num);

#endif