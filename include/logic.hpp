
#ifndef _LOGIC_
#define _LOGIC_
#include <gui_game_widget.hpp>
#include <logic_end_game_data.hpp>
#include <logic_wifi.hpp>
enum logic_tile_display_constants {
    TILE_DISPLAY_HIDDEN = 0,
    TILE_DISPLAY_SHOWN = 1,
    TILE_DISPLAY_FLAGGED = 2,
};

enum logic_tile_value_constants {
    TILE_VALUE_NOT_GENERATED = -2,
    TILE_VALUE_BOMB = -1,
};

enum logic_logic_data_state_constants {
    LOGIC_DATA_STATE_NOT_GENERATED = 0,
    LOGIC_DATA_STATE_GENERATED = 1,
    LOGIC_DATA_STATE_ON_GOING = 2,
    LOGIC_DATA_STATE_LOST = 3,
    LOGIC_DATA_STATE_WON = 4,
    LOGIC_DATA_STATE_TIE,
    LOGIC_DATA_STATE_END,
    LOGIC_DATA_STATE_WAITING,
};

/**
 * This struct stores information about each logic_tile:
 * - `x` x position in the grid in coordinates
 * - `y` y position in the grid in coordinates
 * - `value` number of surrounding bombs[0 - 8] (-1 for bomb logic_tile)
 * - `display` `-2` not generated `0` hidden `1` shown `2` flagged
 */
struct logic_tile {
    int x;
    int y;
    int value;
    int display;
};

/**
 * This struct stores all data that is needed to create a game:
 * - `grid` 2d array of tiles
 * - `mines_total` number of mines that will be generated
 * - `mines_remaining` number of mines that have not been found
 * - `rows` number of rows in the grid
 * - `cols` number of columns in the grid
 * - `state` `0` not generated `1` generated `2` game is ongoing `3` game lost,
 * `4` game won
 * - `seed` number that is used for map generation
 * - `end_data_packet` end_game_data from packet
 * - `end_data_local` local end_game_data
 */

struct gui_game_widget;
struct wifi_data;
struct logic_data {
    gui_game_widget* master;
    logic_tile **grid;
    int mines_total;
    int mines_remaining;
    int hidden_tiles;
    int rows;
    int cols;
    int state;
    int seed;
    logic_end_game_data end_data_packet;
    logic_end_game_data end_data_local;
};

/**
 * @brief Function that creates a grid for logic_data structure
 * @param rows number of rows in the grid
 * @param cols number of columns in grid
 * @return logic_tile**
 */
logic_tile **logic_create_grid(int rows, int cols);

/**
 * @brief Function that creates a logic_data structure
 *
 * @param rows number of rows in the grid
 * @param cols number of columns in grid
 * @param mines_total number of mines that will be put on the grid
 * @param seed number used for map generation
 * @return logic_data
 */
void logic_create_logic_data(logic_data* game_data, int rows, int cols, int mines_total, int seed);

/**
 * @brief Function that generates all values in logic_data grid
 *
 * @param game_data  logic_data struct
 */
void logic_generate_level(logic_data *game_data);

/**
 * @brief Function that randomly generates a single bomb
 *
 * @param game_data logic_data struct
 */
void logic_generate_bomb(logic_data *game_data);

/**
 * @brief Function that generates values for neighbours of bombs
 *
 * @param game_data logica_data struct
 */
void logic_generate_neighbours(logic_data *game_data);

/**
 * @brief Function that handles click on a logic_tile
 *
 * @param x x position in the grid in coordinates
 * @param y x position in the grid in coordinates
 * @param game_data logic_data struct
 */
void logic_click_tile_main(int x, int y, logic_data *game_data);

/**
 * @brief Function that handles click if zero logic_tile is clicked
 *
 * @param x x position in the grid in coordinates
 * @param y x position in the grid in coordinates
 * @param game_data logic_data struct
 */
void logic_click_zero_tile(int x, int y, logic_data *game_data);

/**
 * @brief Function that handles click if non-zero logic_tile is clicked
 *
 * @param x x position in the grid in coordinates
 * @param y x position in the grid in coordinates
 * @param game_data logic_data struct
 */
void logic_click_non_zero_tile(int x, int y, logic_data *game_data);

/**
 * @brief Function that handles click if bomb logic_tile is clicked
 *
 * @param x x position in the grid in coordinates
 * @param y x position in the grid in coordinates
 * @param game_data logic_data struct
 */
void logic_click_bomb_tile(int x, int y, logic_data *game_data);

/**
 * @brief Function that handles when logic_tile is flaged
 *
 * @param x x position in the grid in coordinates
 * @param y x position in the grid in coordinates
 * @param game_data logic_data struct
 */
void logic_click_flag_tile(int x, int y, logic_data *game_data);

/**
 * @brief Function that increases the number of remaining mines
 * @param game_data pointer to logic_data
 */
void logic_mines_remaining_increment(logic_data *game_data);        


/**
 * @brief Function that decreases the number of remaining mines
 * @param game_data pointer to logic_data
 */
void logic_mines_remaining_decrement(logic_data *game_data);

/**
 * @brief Function that deletes logic_data and frees memory
 * @param game_data 
 */
void logic_data_delete(logic_data *game_data);

/**
 * @brief Function that is used to set pointer to gui_game_widget
 * @param game_data pointer to logic_data
 * @param master pointer to gui_game_widget
 */
void logic_data_set_game_widget(logic_data *game_data, gui_game_widget* master);

/**
 * @brief Function that calculates the final score
 * @param game_data pointer to logic_data
 * @return score
 */
int logic_data_calculate_score(logic_data *game_data);

/**
 * @brief Function that is called when the slave sends results to the master
 * @param device wifi_data
 */
void logic_data_master_send_final(wifi_data device);

/**
 * @brief Function that determines if the master can generate the final result
 * @param game_data pointer to logic_data
 * @return bool
 */
bool logic_data_can_generate_result_packet(logic_data *game_data);

/**
 * @brief Function that generates end_game_result for slave
 * @param game_data pointer to logic_data
 * @return logic_end_game_data
 */
logic_end_game_data logic_data_generate_result_packet(logic_data *game_data);

/**
 * @brief Function that is called when you need to display results
 * @param game_data 
 */
void logic_data_handle_end_screen(logic_data *game_data);

/**
 * @brief Function that is called when the slave receives the final result from the master
 * @param device wifi_data
 */
void logic_data_handle_slave_receive_final(wifi_data device);

#endif