#ifndef _GUI_
#define _GUI_
#include <lvgl.h>
#include <logic.hpp>
struct gridWidget{
    lv_obj_t* div;
    lv_obj_t* matrix;
    char** displayValues;
    int rows;
    int columns;
};

struct dataMatrixCallback{
    gridWidget* grid;
    logicData* gameData;
};

//Function that creates widget with gameData and pointer to parent element
void createGridWidget(gridWidget* grid,logicData* gameData,lv_obj_t* parent);

//Return pointer for div element of GridWidget
void createGridWidgetDiv(gridWidget* grid,lv_obj_t* parent, int width, int height);

//Create values that will be put on matrix
void createGridWidgetDisplayValues(gridWidget* grid, int rows, int columns);

//Create lvgl button matrix
void createGridWidgetMatrix(gridWidget* grid, int rows, int colmuns,logicData* gameData);

//Refsreshes display values
void refreshGridWidgetDisplayValues(dataMatrixCallback* cbData);

//Callback for handling clikcs on matrix
void matrixCallback (lv_event_t * e);

//Testing button matrix in lvgl
void testMatrix(int x, int y, lv_obj_t* parent);

//Test body which will contain scrollable matrix
void testBody(int x, int y, lv_obj_t* parent);


#endif