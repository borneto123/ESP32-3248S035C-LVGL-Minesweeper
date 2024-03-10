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
            grid[i][j].status = 0;
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
    generateOthers(gameData);
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

//Offsets
int neighbor[8][2]={
    {-1, -1}, {-1, 0}, {-1, +1},
    { 0, -1},          { 0, +1},
    {+1, -1}, {+1, 0}, {+1, +1}
};

void generateOthers(logicData* gameData){
    for(int i = 0; i < gameData->rows; i++){
        for(int j = 0; j < gameData->columns; j++){
            if(gameData->grid[i][j].value!=-1){
               int tempValue=0;
               for(int k=0; k<8; k++){
                    //Check if neighbor is in bounds
                    if(i+neighbor[k][0]>=0 && i+neighbor[k][0]<gameData->rows && j+neighbor[k][1]>=0 && i+neighbor[k][1]<gameData->columns){
                        if(gameData->grid[i+neighbor[k][0]][j+neighbor[k][1]].value==-1) tempValue++;
                    }
               }
               gameData->grid[i][j].value = tempValue;
            }
        }
    }
}