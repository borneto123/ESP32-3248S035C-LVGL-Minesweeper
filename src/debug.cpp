#include <Arduino.h>
#include <debug.hpp>

void debug_print_grid_value(logic_data game_data) {
    for (int i = 0; i < game_data.rows; i++) {
        Serial.println();
        for (int j = 0; j < game_data.cols; j++)
            Serial.printf("%3d ", game_data.grid[i][j].value);
    }
}

void debug_print_grid_display(logic_data game_data) {
    Serial.println();
    for (int i = 0; i < game_data.rows; i++) {
        Serial.println();
        for (int j = 0; j < game_data.cols; j++) {
            Serial.printf("%3d ", game_data.grid[i][j].display);
        }
    }
}

void debug_print_user_perspective(logic_data game_data) {
    for (int i = 0; i < game_data.rows; i++) {
        Serial.println();
        for (int j = 0; j < game_data.cols; j++) {
            if (game_data.grid[i][j].display == 2) Serial.printf(" F  ");
            if (game_data.grid[i][j].display == 1)
                Serial.printf("%3d ", game_data.grid[i][j].display);

            if (game_data.grid[i][j].display == 0) Serial.printf(" ?  ");
        }
    }
}
void count_mines(logic_data game_data) {
    int count = 0;
    for (int i = 0; i < game_data.rows; i++) {
        for (int j = 0; j < game_data.cols; j++) {
            if (game_data.grid[i][j].value == TILE_VALUE_BOMB) count++;
        }
    }
    Serial.printf("\nMine number: %d", count);
}

void print_hidden_tiles(logic_data game_data) {
    Serial.printf("\nCurrent hidden tiles remaining: %d", game_data.hidden_tiles);
}

void test_hidden_tiles(logic_data game_data) {
    int realCount = 0;
    for (int i = 0; i < game_data.rows; i++) {
        for (int j = 0; j < game_data.cols; j++) {
            if (game_data.grid[i][j].value != TILE_VALUE_BOMB &&
                game_data.grid[i][j].display != TILE_DISPLAY_SHOWN)
                realCount++;
        }
    }
    Serial.println("-------------------------------------");
    Serial.printf("\nReal count:%d", realCount);
    Serial.printf("\nFast count:%d", game_data.hidden_tiles);
    Serial.printf("\nCheck: %d", realCount == game_data.hidden_tiles);
    Serial.println("\n-------------------------------------");
}