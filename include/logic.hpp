
#ifndef _LOGIC_
#define _LOGIC_
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
};

/**
 * This struct stores information about each logic_tile:
 * - `x` x position in grid in cordinates
 * - `y` y position in grid in cordinates
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
 * - `rows` number of rows in grid
 * - `cols` number of columns in grid
 * - `state` `0` not generated `1` generated `2` game is ongoing `3` game lost,
 * `4` game won
 */
struct logic_data {
    logic_tile **grid;
    int rows;
    int cols;
    int state;
};

/**
 * @brief Function that creates a grid for logic_data structure
 * @param rows number of rows in grid
 * @param cols number of columns in grid
 * @return logic_tile**
 */
logic_tile **logic_create_grid(int rows, int cols);

/**
 * @brief Function that creates a logic_data structure
 *
 * @param rows number of rows in grid
 * @param cols number of columns in grid
 * @return logic_data
 */
logic_data logic_create_logic_data(int rows, int cols);

/**
 * @brief Fucntion that generates all values in logic_data grid
 *
 * @param mine_number number of mines that will be put in grid
 * @param game_data  logic_data struct
 */
void logic_generate_level(int mine_number, logic_data *game_data);

/**
 * @brief Funcation that randomly generates a single bomb
 *
 * @param game_data logic_data struct
 */
void logic_generate_bomb(logic_data *game_data);

/**
 * @brief Funcation that generates values for neighbours of bombs
 *
 * @param game_data logica_data struct
 */
void logic_generate_neighbours(logic_data *game_data);

/**
 * @brief Function that handles click on a logic_tile
 *
 * @param x x position in grid in cordinates
 * @param y x position in grid in cordinates
 * @param game_data logic_data struct
 */
void logic_click_tile_main(int x, int y, logic_data *game_data);

/**
 * @brief Function that handles click if zero logic_tile is clicked
 *
 * @param x x position in grid in cordinates
 * @param y x position in grid in cordinates
 * @param game_data logic_data struct
 */
void logic_click_zero_tile(int x, int y, logic_data *game_data);

/**
 * @brief Function that handles click if non zero logic_tile is clicked
 *
 * @param x x position in grid in cordinates
 * @param y x position in grid in cordinates
 * @param game_data logic_data struct
 */
void logic_click_non_zero_tile(int x, int y, logic_data *game_data);

/**
 * @brief Function that handles click if bomb logic_tile is clicked
 *
 * @param x x position in grid in cordinates
 * @param y x position in grid in cordinates
 * @param game_data logic_data struct
 */
void logic_click_bomb_tile(int x, int y, logic_data *game_data);

/**
 * @brief Function that handles when logic_tile is flaged
 *
 * @param x x position in grid in cordinates
 * @param y x position in grid in cordinates
 * @param game_data logic_data struct
 */
void logic_click_flag_tile(int x, int y, logic_data *game_data);

// TO-DO
void deleteGrid(logic_tile **grid);
#endif