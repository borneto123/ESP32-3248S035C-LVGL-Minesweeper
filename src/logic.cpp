

#include <Arduino.h>

#include <debug.hpp>
#include <logic.hpp>
#include <queue>

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

logic_data logic_create_logic_data(int rows, int cols) {
    logic_data game_data;

    game_data.grid = logic_create_grid(rows, cols);
    game_data.rows = rows;
    game_data.cols = cols;
    game_data.state = LOGIC_DATA_STATE_NOT_GENERATED;

    return game_data;
}

void logic_generate_level(int mine_number, logic_data *game_data) {
    randomSeed(millis());

    for (int i = 0; i < mine_number; i++) {
        logic_generate_bomb(game_data);
    }
    logic_generate_neighbours(game_data);
}

void logic_generate_bomb(logic_data *game_data) {
    int x;
    int y;
    do {
        x = random(0, game_data->rows);
        y = random(0, game_data->cols);
    } while (game_data->grid[x][y].value != TILE_VALUE_NOT_GENERATED && game_data->grid[x][y].value != TILE_VALUE_BOMB);
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
    if (game_data->grid[x][y].value == 0) {
        logic_click_zero_tile(x, y, game_data);
    } else if (game_data->grid[x][y].value == TILE_VALUE_BOMB) {
        logic_click_bomb_tile(x, y, game_data);
    } else {
        logic_click_non_zero_tile(x, y, game_data);
    }
    debug_print_grid_display(*game_data);
}

void logic_click_bomb_tile(int x, int y, logic_data *game_data) {
    game_data->state = LOGIC_DATA_STATE_LOST;
    Serial.println("Game lost");
}

void logic_click_non_zero_tile(int x, int y, logic_data *game_data) {
    game_data->grid[x][y].display = TILE_DISPLAY_SHOWN;
}

// FIX DONE WATCH FOR BUGS :)
void logic_click_flag_tile(int x, int y, logic_data *game_data) {
    if (game_data->grid[x][y].display == TILE_DISPLAY_HIDDEN)
        game_data->grid[x][y].display = TILE_DISPLAY_FLAGGED;
    else if (game_data->grid[x][y].display == TILE_DISPLAY_FLAGGED)
        game_data->grid[x][y].display = TILE_DISPLAY_HIDDEN;
}

void logic_click_zero_tile(int x, int y, logic_data *game_data) {
    queue<logic_tile *> flood;
    game_data->grid[x][y].display = TILE_DISPLAY_SHOWN;
    flood.push(&game_data->grid[x][y]);

    while (flood.size() != 0) {
        logic_tile *grid = flood.front();
        flood.pop();
        int count = 0;
        grid->display = TILE_DISPLAY_SHOWN;
        for (int k = 0; k < 8; k++) {
            int x = grid->x + neighbor[k][0];
            int y = grid->y + neighbor[k][1];
            if (x >= 0 && x < game_data->rows && y >= 0 &&
                y < game_data->cols) {
                if (game_data->grid[x][y].value == 0 &&
                    game_data->grid[x][y].display == TILE_DISPLAY_HIDDEN) {
                    flood.push(&game_data->grid[x][y]);
                    count++;
                }
            }
            if (count == 0) {
                for (int k = 0; k < 8; k++) {
                    int x = grid->x + neighbor[k][0];
                    int y = grid->y + neighbor[k][1];
                    if (x >= 0 && x < game_data->rows && y >= 0 && y < game_data->cols) {
                        if (game_data->grid[x][y].value != 0 && game_data->grid[x][y].display == TILE_DISPLAY_HIDDEN) {
                            game_data->grid[x][y].display = TILE_DISPLAY_SHOWN;
                        }
                    }
                }
            }
        }
    }
}