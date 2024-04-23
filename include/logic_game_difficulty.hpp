#ifndef _DIFFICULTY_LOGIC_
#define _DIFFICULTY_LOGIC_

enum logic_game_difficulty_constant{
    GAME_DIFFICULTY_SET_ROWS,
    GAME_DIFFICULTY_SET_COLS,
    GAME_DIFFICULTY_SET_MINES,
    GAME_DIFFICULTY_SET_SEED,
};

/**
 * This struct stores information about game difficulty:
 * - `rows` number of rows in the grid
 * - `cols` number of columns in the grid
 * - `mines` number of mines
 * - `seed` number that is used for map generation
 */
struct logic_game_difficulty{
    int rows;
    int cols;
    int mines;
    int seed;
};

/**
 * @brief Function that creates difficulty
 * @param difficulty pointer to logic_game_difficulty 
 * @param rows number of rows in the grid
 * @param cols number of columns in the grid
 * @param mines number of mines
 * @param seed number that is used for map generation
 */
void logic_game_difficulty_create(logic_game_difficulty* difficulty, int rows, int cols, int mines,int seed);

/**
 * @brief Function that enables changing properties of difficulty(This function is not used in this version)
 * @param difficulty pointer to logic_game_difficulty struct
 * @param opt value that you want to change (logic_game_difficulty_constant)
 * @param value value to which will the property be set
 */
void logic_game_difficulty_set(logic_game_difficulty* difficulty, int opt, int value);

#endif