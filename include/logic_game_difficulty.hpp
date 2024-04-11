#ifndef _DIFFICULTY_LOGIC_
#define _DIFFICULTY_LOGIC_

enum logic_game_difficulty_constant{
    GAME_DIFFICULTY_SET_ROWS,
    GAME_DIFFICULTY_SET_COLS,
    GAME_DIFFICULTY_SET_MINES,
    GAME_DIFFICULTY_SET_SEED,
};

struct logic_game_difficulty{
    int rows;
    int cols;
    int mines;
    int seed;
};

void logic_game_difficulty_create(logic_game_difficulty* difficulty, int rows, int cols, int mines,int seed);

void logic_game_difficulty_set(logic_game_difficulty* difficulty, int opt, int value);

#endif