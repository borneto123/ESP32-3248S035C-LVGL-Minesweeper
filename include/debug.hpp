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
 * @brief Function that prints display of every logic_tile in the grid
 * 
 * @param game_data logic_data struct
 */
void debug_print_grid_display(logic_data game_data);


/**
 * @brief Function that prints perspective of the user
 * 
 * @param game_data logic_data struct
 */
void debug_print_user_perspective(logic_data game_data);


//Provjeri jel radi za sve
#endif