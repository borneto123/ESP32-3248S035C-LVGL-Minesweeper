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

void printGridStatus(logicData gameData){

   for(int i = 0; i < gameData.rows; i++){
        Serial.println();
        for(int j = 0; j < gameData.columns; j++){
            Serial.printf("%3d ",gameData.grid[i][j].status);
    }
   }
}

void printUserPerspective(logicData gameData){

   for(int i = 0; i < gameData.rows; i++){
        Serial.println();
        for(int j = 0; j < gameData.columns; j++){

         if(gameData.grid[i][j].status==2) Serial.printf(" F  ");
         if(gameData.grid[i][j].status==1) Serial.printf("%3d ",gameData.grid[i][j].status);;
         if(gameData.grid[i][j].status==0) Serial.printf(" ?  ");
    }
   }
}