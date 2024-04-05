#include <logic_game_difficulty.hpp>

void logic_game_difficulty_create(logic_game_difficulty* difficulty, int rows, int cols, int mines){
    difficulty->rows = rows;
    difficulty->cols = cols;
    difficulty->mines = mines;
}

void logic_game_difficulty_set(logic_game_difficulty* difficulty, int opt, int value){

    if(opt == GAME_DIFFICULTY_SET_ROWS){
        difficulty->rows = value;
    }
    else if(opt == GAME_DIFFICULTY_SET_COLS){
        difficulty->cols = value;
    }
    else if(opt == GAME_DIFFICULTY_SET_MINES){
        difficulty->cols = value;
    }
}
