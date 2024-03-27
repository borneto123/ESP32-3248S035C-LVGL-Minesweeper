#include <logic.hpp>
#include <gui.hpp>
#ifndef _LOGIC_DEBUG_
#define _LOGIC_DEBUG_


struct cords{
    int x;
    int y;
};
//Prints data in game grid
void printGridValue(logicData gameData);

void printGridStatus(logicData gameData);

void printUserPerspective(logicData gameData);

cords convertIdToCordinates(int id,int columns);
//Provjeri jel radi za sve
int getColumnsFromDisplayValues(gridWidget* grid);
#endif