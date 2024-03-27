
#ifndef _LOGIC_
#define _LOGIC_

// -2 ------------> variable not decalred
struct tile{
    int posX;       // X position in grid
    int posY;       // Y position in grid
    int value;      // Number of surrounding bombs from 0-8 (-1 marks that tile is a bomb)
    int status;     // 0 - hidden, 1 - shown, 2 - flagged
};

struct logicData{
    tile** grid;    // 2d array of tiles
    int rows;       // number of rows
    int columns;    // bznber of columns
    int state;      // 0 not generate, 1 generated, 2 game is ongoing, 3 game lost, 4 game won
};


//Function that returns pointer to grid
tile** createGrid(int rows, int columns);
logicData createLogicData(int rows, int columns);


//Generating bombs and values for every tile
void generateLevel(int mineNumber, logicData* gameData);

//Generates 1 bomb
void generateBomb(logicData* gameData);

//Generates non bomb tiles
void generateOthers(logicData* gameData);

//Handle clicking of a tile
void clickTile(int x, int y, logicData* gameData);

//Flood fill for tiles with value 0
void clickZeroTile(int x, int y, logicData* gameData);

//Function to fill non zero tiles without bombs
void clickNonZeroTile(int x, int y, logicData* gameData);

//Handle clicking of a bomb tile
void clickBombTile(int x, int y, logicData* gameData);

//Handle flaging a tile
void clickFlagBombTile(int x, int y, logicData* gameData);

//Maybe usefull
void refreshShown();

//Frees memory
void deleteGrid(tile** grid);
#endif