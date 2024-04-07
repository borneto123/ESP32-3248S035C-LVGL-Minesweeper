#include <debug.hpp>
#include <Arduino.h>
void debug_print_grid_value(logic_data game_data){

   for(int i = 0; i < game_data.rows; i++){
        Serial.println();
        for(int j = 0; j < game_data.cols; j++){
            Serial.printf("%3d ",game_data.grid[i][j].value);
    }
   }
}

void debug_print_grid_display(logic_data game_data){
   Serial.println();
   for(int i = 0; i < game_data.rows; i++){
        Serial.println();
        for(int j = 0; j < game_data.cols; j++){
            Serial.printf("%3d ",game_data.grid[i][j].display);
    }
   }
}

void debug_print_user_perspective(logic_data game_data){

   for(int i = 0; i < game_data.rows; i++){
        Serial.println();
        for(int j = 0; j < game_data.cols; j++){

         if(game_data.grid[i][j].display==2) Serial.printf(" F  ");
         if(game_data.grid[i][j].display==1) Serial.printf("%3d ",game_data.grid[i][j].display);;
         if(game_data.grid[i][j].display==0) Serial.printf(" ?  ");
    }
   }
}
void count_mines(logic_data game_data){
   int count = 0;
   for(int i=0; i<game_data.rows; i++){
      for(int j=0; j<game_data.cols; j++){
         if(game_data.grid[i][j].value == TILE_VALUE_BOMB) count++;
      }
   }
   Serial.printf("Mine number: %d", count);
}

