#include <logic_debug.hpp>
#include <Arduino.h>
void printGridValue(logicData gameData){

   for(int i = 0; i < gameData.rows; i++){
        Serial.println();
        for(int j = 0; j < gameData.columns; j++){
            Serial.printf("%3d ",gameData.grid[i][j].value);
    }
   }
}