#ifndef _GAME_MODE_
#define _GAME_MODE_
#include <lvgl.h>
#include <gui_menu.hpp>

struct gui_menu;

/**
 * This struct stores information about game_mode_menu:
 * - `div` pointer to parent of all elements
 * - `header` label that will be displayed at the top of the screen
 * - `singleplayer_button` button that starts singleplayer
 * - `multiplayer_button` button that starts multiplayer
 * - `difficulty_menu` pointer to gui_menu
 */
struct gui_game_mode_menu{
    lv_obj_t* div;
    lv_obj_t* header;
    lv_obj_t* singleplayer_button;
    lv_obj_t* multiplayer_button;
    gui_menu* difficulty_menu;
};

/**
 * @brief Function that creates a menu for selecting game mode
 * @param mode_menu pointer to gui_game_mode_menu
 * @param parent pointer to parent 
 * @param difficulty_menu pointer to gui_menu
 */
void gui_game_mode_menu_create(
    gui_game_mode_menu* mode_menu,
    lv_obj_t* parent,
    gui_menu* difficulty_menu
);

/**
 * @brief Function that creates div of gui_game_mode_menu_widget
 * @param mode_menu pointer to gui_game_mode_menu
 * @param parent pointer to parent
 */
void gui_game_mode_menu_create_div(gui_game_mode_menu* mode_menu, lv_obj_t* parent);

/**
 * @brief Function that creates the singleplayer button
 * @param mode_menu pointer to gui_game_mode_menu
 * @param parent pointer to parent
 * @param color_text text color
 * @param color_bg background color
 */
void gui_game_mode_menu_create_singleplayer_button(
    gui_game_mode_menu* mode_menu,
    lv_obj_t* parent,
    lv_color_t color_text,
    lv_color_t color_bg
);

/**
 * @brief Function that creates the multiplayer button
 * @param mode_menu pointer to gui_game_mode_menu
 * @param parent pointer to parent
 * @param color_text text color
 * @param color_bg background color
 */
void gui_game_mode_menu_create_multiplayer_button(
    gui_game_mode_menu* mode_menu,
    lv_obj_t* parent,
    lv_color_t color_text,
    lv_color_t color_bg
);

/**
 * @brief Function that creates text at the top of the screen
 * @param mode_menu pointer to gui_game_mode_menu
 * @param parent pointer to parent
 */
void gui_game_mode_menu_create_header(gui_game_mode_menu* mode_menu, lv_obj_t* parent);

/**
 * @brief Callback function for the Singleplayer button
 * @param e lv_event_t*
 */
void gui_game_mode_menu_singleplayer_button_cb(lv_event_t* e);

/**
 * @brief Callback function for the Multiplayer button
 * @param e lv_event_t*
 */
void gui_game_mode_menu_multiplayer_button_cb(lv_event_t* e);

/**
 * @brief Function that makes game mode menu visible
 * @param mode_menu pointer to gui_game_mode_menu
 */
void gui_game_mode_menu_show(gui_game_mode_menu* mode_menu);

/**
 * @brief Function that makes game mode menu invisible
 * @param mode_menu pointer to gui_game_mode_menu
 */
void gui_game_mode_menu_hide(gui_game_mode_menu* mode_menu);

#endif