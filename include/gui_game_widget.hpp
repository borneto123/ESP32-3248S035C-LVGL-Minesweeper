#ifndef _GAME_
#define _GAME_
#include <gui_grid_widget.hpp>
#include <gui_timer_widget.hpp>
#include <gui_mine_counter_widget.hpp>
#include <logic.hpp>
#include <logic_game_difficulty.hpp>
#include <gui_end_screen_widget.hpp>
struct gui_grid_widget;
struct gui_mine_counter_widget;


/**
 * This struct stores information about gui_game_widget:
 * - `div` pointer to button matrix parent
 * - `back_button` button for deleting game_widget 
 * - `master_grid_data` pointer to logic_data
 * - `master_grid` pointer to gui_grid_widget
 * - `master_timer` pointer to gui_timer_widget
 * - `master_counter` pointer to gui_mine_counter_widget
 * - `result` lv object that displays the result of the game(gui_end_game_widget)
 * - `started` used to see if structs are created
 * - `online_mode` `0` Singleplayer `1` Multiplayer
 */
struct gui_game_widget{
    lv_obj_t* div;
    lv_obj_t* back_button;
    logic_data* master_grid_data;
    gui_grid_widget* master_grid;
    gui_timer_widget* master_timer;
    gui_mine_counter_widget* master_counter;
    lv_obj_t* result;
    bool started = false;
    int online_mode;
};

/**
 * @brief Function that creates game_widget
 * @param master pointer to gui_game_widget
 * @param difficulty value of difficulty(logic_game_difficulty)
 * @param parent pointer to parent
 */
void gui_game_widget_create(
    gui_game_widget* master,
    logic_game_difficulty difficulty,
    lv_obj_t* parent
);

/**
 * @brief Function that creates parent of gui_game_widget
 * @param master pointer to 
 * @param difficulty gui_game_widget
 * @param parent pointer to parent
 */
void gui_game_widget_create_div(
    gui_game_widget* master,
    logic_game_difficulty difficulty,
    lv_obj_t* parent
);

/**
 * @brief Function that creates back batton(Button for deleting game widget)
 * @param master 
 * @param parent 
 */
void gui_game_widget_create_button(
    gui_game_widget* master,
    lv_obj_t* parent
);

/**
 * @brief Callback function to handle the click event on the back button
 * @param e lv_event_t*
 */
void gui_game_widget_button_cb(lv_event_t* e);

/**
 * @brief Function that deletes gui_game_widget and frees memory
 * @param master pointer to gui_game_widget
 */
void gui_game_widget_delete(gui_game_widget* master);

/**
 * @brief Function that sets the online_mode to 0
 * @param master pointer to gui_game_widget
 */
void gui_game_widget_singleplayer(gui_game_widget* master);

/**
 * @brief Function that sets the online_mode to 1
 * @param master pointer to gui_game_widget
 */
void gui_game_widget_multiplayer(gui_game_widget* master);
#endif