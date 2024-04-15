#include <Arduino.h>

#include <debug.hpp>
#include <logic.hpp>
#include <queue>
#include <gui_end_screen_widget.hpp>
#include <logic_end_game_data.hpp>
#include <gui_timer_widget.hpp>


using namespace std;

logic_tile **logic_create_grid(int rows, int cols) {
    logic_tile **grid = new logic_tile *[rows];
    
    for (int i = 0; i < rows; i++) {
        grid[i] = new logic_tile[cols];
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            grid[i][j].x = i;
            grid[i][j].y = j;
            grid[i][j].value = TILE_VALUE_NOT_GENERATED;
            grid[i][j].display = TILE_DISPLAY_HIDDEN;
        }
    }
    return grid;
}

void logic_create_logic_data(logic_data* game_data, int rows, int cols, int mines_total, int seed) {
    
    game_data->seed = seed;
    game_data->grid = logic_create_grid(rows, cols);
    game_data->rows = rows;
    game_data->cols = cols;
    game_data->mines_total = mines_total;
    game_data->mines_remaining = mines_total;
    game_data->hidden_tiles = rows * cols - mines_total;
    game_data->state = LOGIC_DATA_STATE_NOT_GENERATED;
    logic_generate_level(game_data);
}

void logic_generate_level(logic_data *game_data) {
    if(game_data->seed == NULL)
    game_data->seed = millis()%65535;//Check this later
    randomSeed(game_data->seed);

    for (int i = 0; i < game_data->mines_total; i++) {
        logic_generate_bomb(game_data);
    }
    logic_generate_neighbours(game_data);
    count_mines(*game_data);
}

void logic_generate_bomb(logic_data *game_data) {
    int x;
    int y;
    do {
        x = random(0, game_data->rows);
        y = random(0, game_data->cols);
       // Serial.printf("\nMine false x:%d, y:%d, value:%d",x,y,game_data->grid[x][y].value);
    } while (!(game_data->grid[x][y].value == TILE_VALUE_NOT_GENERATED && game_data->grid[x][y].value != TILE_VALUE_BOMB));
    //Serial.printf("\nMine true x:%d, y:%d, value:%d",x,y,game_data->grid[x][y].value);
    game_data->grid[x][y].value = TILE_VALUE_BOMB;
}
// Array that makes finding neighbours easier
int neighbor[8][2] = {{-1, -1}, {-1, 0}, {-1, +1}, {0, -1}, {0, +1}, {+1, -1}, {+1, 0}, {+1, +1}};

void logic_generate_neighbours(logic_data *game_data) {
    for (int i = 0; i < game_data->rows; i++) {
        for (int j = 0; j < game_data->cols; j++) {
            if (game_data->grid[i][j].value != -1) {
                int tempValue = 0;
                for (int k = 0; k < 8; k++) {
                    // Check if neighbor is in bounds
                    int x = i + neighbor[k][0];
                    int y = j + neighbor[k][1];
                    if (x >= 0 && x < game_data->rows && y >= 0 && y < game_data->cols) {
                        if (game_data->grid[x][y].value == TILE_VALUE_BOMB)
                            tempValue++;
                    }
                }
                game_data->grid[i][j].value = tempValue;
            }
        }
    }
}

void logic_click_tile_main(int x, int y, logic_data *game_data) {
    if(game_data->state != LOGIC_DATA_STATE_LOST && game_data->state!=LOGIC_DATA_STATE_WON){
        if (game_data->grid[x][y].display != TILE_DISPLAY_FLAGGED && game_data->grid[x][y].display != TILE_DISPLAY_SHOWN) {
        if (game_data->grid[x][y].value == 0) {
            logic_click_zero_tile(x, y, game_data);
        } 
        else if (game_data->grid[x][y].value == TILE_VALUE_BOMB) {
            logic_click_bomb_tile(x, y, game_data);
        } 
        else {
            logic_click_non_zero_tile(x, y, game_data);
        }
    }
    //debug_print_grid_display(*game_data);1
    test_hidden_tiles(*game_data);
    if(game_data->hidden_tiles == 0){
        game_data->state = LOGIC_DATA_STATE_WON;
        gui_end_screen_widget* won = new gui_end_screen_widget;
        logic_end_game_data* end_data = new logic_end_game_data;
        end_data->score = logic_data_calculate_score(game_data);
        gui_timer_widget_stop(game_data->master->master_timer);
        end_data->time = game_data->master->master_timer->current_time;
        end_data->state = LOGIC_DATA_STATE_WON;
        gui_end_screen_widget_create(won, *end_data);
    }
    }
    print_hidden_tiles(*game_data);
}

void logic_click_bomb_tile(int x, int y, logic_data *game_data) {
    game_data->state = LOGIC_DATA_STATE_LOST;
    Serial.println("Game lost");

    gui_end_screen_widget* lost = new gui_end_screen_widget;
    
    
    game_data->end_data_local.score = logic_data_calculate_score(game_data);
    gui_timer_widget_stop(game_data->master->master_timer);
    game_data->end_data_local.time = game_data->master->master_timer->current_time;
    Serial.printf("\nOnline mode: %d\n",game_data->master->online_mode);
    if(game_data->master->online_mode == 0){
    game_data->end_data_local.state = LOGIC_DATA_STATE_LOST;
    }
    if(game_data->master->online_mode == 1){
        game_data->end_data_local.state = LOGIC_DATA_STATE_WAITING;
        if(wifi_device_type() == WIFI_DEVICE_SLAVE){
            wifi_send_result_slave(game_data->end_data_local);
        }
        if(wifi_device_type() == WIFI_DEVICE_MASTER){
            if(game_data->end_data_packet.state = LOGIC_DATA_STATE_WAITING){
                // Send result
            }
        }
    }
    gui_end_screen_widget_create(lost, game_data->end_data_local);
}

void logic_click_non_zero_tile(int x, int y, logic_data *game_data) {
    game_data->grid[x][y].display = TILE_DISPLAY_SHOWN;
    game_data->hidden_tiles--; // Check 
}

//WATCH FOR BUGS :)
void logic_click_flag_tile(int x, int y, logic_data *game_data) {
    if(game_data->state != LOGIC_DATA_STATE_LOST && game_data->state!=LOGIC_DATA_STATE_WON){
    if (game_data->grid[x][y].display == TILE_DISPLAY_HIDDEN) {
        game_data->grid[x][y].display = TILE_DISPLAY_FLAGGED;
        logic_mines_remaining_decrement(game_data);      
    }
    else if (game_data->grid[x][y].display == TILE_DISPLAY_FLAGGED) {
        game_data->grid[x][y].display = TILE_DISPLAY_HIDDEN;
        logic_mines_remaining_increment(game_data);
    }
    }
}

void logic_mines_remaining_increment(logic_data *game_data){
    game_data->mines_remaining++;
}


void logic_mines_remaining_decrement(logic_data *game_data){
    game_data->mines_remaining--;
}

void logic_click_zero_tile(int x, int y, logic_data *game_data) {
    queue<logic_tile*> flood;
    game_data->grid[x][y].display = TILE_DISPLAY_SHOWN;
    game_data->hidden_tiles--;
    flood.push(&game_data->grid[x][y]);

    while (flood.size() != 0) {
        logic_tile *grid = flood.front();
        flood.pop();
        //grid->display = TILE_DISPLAY_SHOWN;
        
        for (int k = 0; k < 8; k++) {
            int x = grid->x + neighbor[k][0];
            int y = grid->y + neighbor[k][1];
            if (x >= 0 && x < game_data->rows && y >= 0 &&
                y < game_data->cols) {
                if (game_data->grid[x][y].value == 0 &&
                    game_data->grid[x][y].display == TILE_DISPLAY_HIDDEN) {
                    flood.push(&game_data->grid[x][y]);
                    game_data->grid[x][y].display = TILE_DISPLAY_SHOWN;
                    game_data->hidden_tiles--;
                }
            }
            
                for (int k = 0; k < 8; k++) {
                    int x = grid->x + neighbor[k][0];
                    int y = grid->y + neighbor[k][1];
                    if (x >= 0 && x < game_data->rows && y >= 0 && y < game_data->cols) {
                        if (game_data->grid[x][y].value != 0 && game_data->grid[x][y].display == TILE_DISPLAY_HIDDEN) {
                            game_data->grid[x][y].display = TILE_DISPLAY_SHOWN;
                            game_data->hidden_tiles--;
                        }
                    }
                }
            
        }
    }
}

void logic_data_delete(logic_data *game_data){

    delete[] game_data->grid;
}

void logic_data_set_game_widget(logic_data *game_data, gui_game_widget* master){
    game_data->master = master;
}
int logic_data_calculate_score(logic_data *game_data){
    int tile_num = game_data->rows * game_data->cols - game_data->mines_total;
    return tile_num - game_data->hidden_tiles;
}



void logic_data_slave_master_receive(wifi_data device){
    Serial.println("Test");
    device.menu->master->master_grid_data->end_data_packet = device.receive.end_game_data;
    }