#include <logic.hpp>
#include <Arduino.h>

//Creating 2d array of tiles which will be used in logicData struct
tile** createGrid(int rows, int columns){

    tile** grid = new tile*[rows];
    
    for (int i = 0; i < rows; i++) {
        grid[i] = new tile[columns];
    }

    for(int i = 0; i < rows; i++){
        for(int j = 0; j < columns; j++){
            grid[i][j].posX = i;
            grid[i][j].posY = j;
            grid[i][j].value = -2; 
            grid[i][j].revealed = -2;
            grid[i][j].status = -2;
         }
    }

    return grid;
}

logicData createLogicData(int rows, int columns){
    logicData gameData;
    gameData.grid = createGrid(rows, columns);
    gameData.rows = rows;
    gameData.columns = columns;
    gameData.state = 0;

    return gameData;
}

void generateLevel(int mineNumber, logicData* gameData){
    randomSeed(millis());
    for(int i = 0; i < mineNumber; i++){
        generateBomb(gameData);
    }
}

void generateBomb(logicData* gameData){
    int x;
    int y;
    do{
        x = random(0,gameData->rows);
        y = random(0,gameData->columns);
    }while(gameData->grid[x][y].value==-1);
    gameData->grid[x][y].value=-1;
}


void generateOthers(logicData* gameData){
    for(int i = 0; i < gameData->rows; i++){
        for(int j = 0; j < gameData->columns; j++){
            if(gameData->grid[i][j].value!=-1){
                //Write neighbor logic
            }
        }
    }
}