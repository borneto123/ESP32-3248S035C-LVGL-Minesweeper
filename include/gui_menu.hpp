#ifndef _MENUE_
#define _MENUE_

#include <lvgl.h>
#include <gui_game_difficulty_button.hpp>
#include <logic_wifi.hpp>
#include <gui_game_mode_menu.hpp>

struct wifi_data;
struct gui_game_difficulty_button;
struct gui_game_widget;
struct gui_game_mode_menu;

/**
 * This struct stores information about the difficulty menu:
 * - `div` parent of all objects in the menu 
 * - `easy` button for easy difficulty
 * - `medium` button for medium difficulty
 * - `hard` button for hard difficulty
 * - `mode_menu` pointer to gui_game_mode_menu
 * - `master` pointer to gui_game_widget
 * - `back_button` back button for game_mode_menu
 * - `waiting_label` label that is used for the slave device while waiting for the game packet
 * - `online_mode` `0` Singleplayer `1` Multiplayer
 * - `multiplayer_map_num` used to determine the type of multiplayer
 * - `first` used by slave when multiple games are played
 */
struct gui_menu
{
    lv_obj_t* div;
    gui_game_difficulty_button* easy;
    gui_game_difficulty_button* medium;
    gui_game_difficulty_button* hard;
    gui_game_mode_menu* mode_menu;
    gui_game_widget* master;
    lv_obj_t* back_button;
    lv_obj_t* waiting_label;
    lv_obj_t* header;
    int online_mode;
    int multiplayer_map_num;
    int first = 1;

};

/**
 * @brief Function that creates gui_menu
 * @param menu pointer to gui_menu
 * @param master pointer to gui_game_widget
 * @param parent pointer to parent
 */
void gui_menu_create(gui_menu* menu,gui_game_widget* master, lv_obj_t* parent);

/**
 * @brief Function that creates gui_menu div
 * @param menu pointer to gui_menu
 * @param parent pointer to parent
 */
void gui_menu_create_div(gui_menu* menu, lv_obj_t* parent);

/**
 * @brief Function that creates gui_menu back button
 * @param menu pointer to gui_menu
 * @param parent pointer to parent
 */
void gui_menu_create_back_button(gui_menu* menu, lv_obj_t* parent);

/**
 * @brief Callback function for the back button
 * @param e lv_event_t*
 */
void gui_menu_back_button_cb(lv_event_t* e);

/**
 * @brief Function that makes gui_menu item visible 
 * @param object pointer to object
 */
void gui_menu_item_show(lv_obj_t* object);
/**
 * @brief Function that makes gui_menu item invisible 
 * @param object pointer to object
 */
void gui_menu_item_hide(lv_obj_t* object);

/**
 * @brief Function that sets the online_mode to 0
 * @param master pointer to gui_game_widget
 */
void gui_menu_singleplayer(gui_menu* menu);

/**
 * @brief Function that sets the online_mode to 1
 * @param master pointer to gui_game_widget
 */
void gui_menu_multiplayer(gui_menu* menu, int map_num);

/**
 * @brief Function that creates the waiting label
 * @param menu pointer to gui_menu
 * @param parent pointer to parent
 */
void gui_menu_waiting_create(gui_menu* menu, lv_obj_t* parent);

/**
 * @brief Function that creates "Select difficulty" text
 * @param menu pointer to gui_menu
 * @param parent pointer to parent
 */
void gui_menu_header_create(gui_menu* menu, lv_obj_t* parent);

/**
 * @brief Function for adding styles to header
 * @param header pointer to header object
 */
void gui_menu_header_style_init(lv_obj_t* header);

/**
 * @brief Function for adding styles to waiting_label
 * @param waiting_label pointer to waiting_label object
 */
void gui_menu_waiting_style_init(lv_obj_t* waiting_label);

/**
 * @brief Function that is called when slave receives difficulty
 * @param data wifi_data
 */
void gui_menu_slave_receive_difficulty(wifi_data data);
#endif