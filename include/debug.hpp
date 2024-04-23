#include <logic.hpp>
#include <gui_grid_widget.hpp>
#ifndef _LOGIC_DEBUG_
#define _LOGIC_DEBUG_

/**
 * @brief Function that prints values of every logic_tile in the grid
 * 
 * @param game_data logic_data struct
 */
void debug_print_grid_value(logic_data game_data);

/**
 * @brief Function that prints the display value of every logic_tile in the grid
 * 
 * @param game_data logic_data struct
 */
void debug_print_grid_display(logic_data game_data);

/**
 * @brief Function that prints the perspective of the user
 * 
 * @param game_data logic_data struct
 */
void debug_print_user_perspective(logic_data game_data);

/**
 * @brief Function that counts the number of mines
 * @param game_data logic_data struct
 */
void count_mines(logic_data game_data);

/**
 * @brief Function that prints the number of hidden tiles
 * @param game_data logic_data struct
 */
void print_hidden_tiles(logic_data game_data);

/**
 * @brief Function for testing fast method of counting hidden tiles
 * @param game_data logic_data struct
 */
void test_hidden_tiles(logic_data game_data);
//Provjeri jel radi za sve
#endif