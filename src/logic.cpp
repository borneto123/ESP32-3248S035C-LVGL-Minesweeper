#include <logic.hpp>
#include <Arduino.h>
#include <queue>

using namespace std;

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
    }while(gameData->grid[x][y].value!=-2 && gameData->grid[x][y].value !=-1);
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
                    int x = i+neighbor[k][0];
                    int y = j+neighbor[k][1];
                    if(x>=0 && x<gameData->rows && y>=0 && y<gameData->columns){
                        if(gameData->grid[x][y].value==-1) tempValue++;
                    }
               }
               gameData->grid[i][j].value = tempValue;
            }
        }
    }
}

void clickTile(int x, int y, logicData* gameData){

    if(gameData->grid[x][y].value == 0){
        clickZeroTile(x,y,gameData);
    }
    else if(gameData->grid[x][y].value == -1){
        clickBombTile(x,y,gameData);
    }
    else{
        clickNonZeroTile(x,y,gameData);
    }
}

void clickBombTile(int x, int y, logicData* gameData){
    gameData->state=3;
    Serial.println("Game lost");
}

void clickNonZeroTile(int x, int y, logicData* gameData){

    gameData->grid[x][y].status = 1;

}

void clickFlagBombTile(int x, int y, logicData* gameData){
    gameData->grid[x][y].status = 2;
}

  void clickZeroTile(int x, int y, logicData* gameData){
    
    queue<tile*> flood;
    gameData->grid[x][y].status = 1;
    flood.push(&gameData->grid[x][y]);

    while(flood.size() !=0){
        tile* grid =  flood.front();
        flood.pop();

        grid->status=1;
        for(int k = 0; k < 8; k++){

            int x = grid->posX+neighbor[k][0];
            int y = grid->posY+neighbor[k][1];
            if(x>=0 && x<gameData->rows && y>=0 && y<gameData->columns){
                if(gameData->grid[x][y].value == 0 && gameData->grid[x][y].status == 0){
                    flood.push(&gameData->grid[x][y]);
                }
            }
        }
    }

}  