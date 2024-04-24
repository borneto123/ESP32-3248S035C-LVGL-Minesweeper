#ifndef _END_DATA_
#define _END_DATA_

/**
 * This struct stores information about end_game:
 * - `type` type of packet when used for Multiplayer
 * - `state` state of the game
 * - `time` passed time
 * - `score` 
 */
struct logic_end_game_data{
    int type;
    int state; 
    unsigned long int time;
    int score;
};


#endif