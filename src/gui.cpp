#include <gui.hpp>
#include <lvgl.h>
#include <Arduino.h>
#include <debug.hpp>
void testMatrix(int row, int columns, lv_obj_t* parent){
    
    lv_obj_t* matrix;
    matrix = lv_btnmatrix_create(parent);
    lv_obj_set_size(matrix,columns*40,row*40); 
    int mapSize = columns*row+row;
    int labelSize;
    static char** map = new char*[mapSize];
    for(int i=0; i<mapSize-1; i++){
        map[i] = new char[3];
        if((i+1)%(columns+1)==0) map[i] = "\n";
        else map[i] = "  ";
        Serial.printf("%s",map[i]);
    }
    map[mapSize-1] = NULL;
    lv_btnmatrix_set_map(matrix, (const char**)map);
    map[5] = "B";
    static lv_style_t style_bg;
    lv_style_init(&style_bg);
    lv_style_set_pad_all(&style_bg, 0);
    lv_style_set_pad_gap(&style_bg, 0);
    lv_style_set_border_width(&style_bg, 0);

    lv_obj_add_style(matrix, &style_bg, 0);
}

void testBody(int x, int y, lv_obj_t* parent){
    lv_obj_t* div = lv_obj_create(parent);
    lv_obj_set_size(div,x,y);
    lv_obj_align(div, LV_ALIGN_BOTTOM_MID, 0, 0);
    lv_obj_clear_flag(div, LV_OBJ_FLAG_SCROLL_ELASTIC);
    testMatrix(7,6,div);
}

void createGridWidget(gridWidget* grid,logicData* gameData,lv_obj_t* parent){
    grid->columns=gameData->columns;
    grid->rows = gameData->rows;
    createGridWidgetDiv(grid,parent,LV_HOR_RES,400);
    createGridWidgetDisplayValues(grid, gameData->rows,gameData->columns);
    createGridWidgetMatrix(grid,gameData->rows,gameData->columns,gameData);
}

void createGridWidgetDisplayValues(gridWidget* grid, int rows, int columns){
    int mapSize = columns*rows+rows;
    grid->displayValues= new char*[mapSize];
    for(int i=0; i<mapSize-1; i++){
        grid->displayValues[i] = new char[3];
        if((i+1)%(columns+1)==0) grid->displayValues[i] = "\n";
        else //grid->displayValues[i] = "  ";
        sprintf(grid->displayValues[i],"  ");
        Serial.printf("%s",grid->displayValues[i]);
    }
    grid->displayValues[mapSize-1] = NULL;
}
void createGridWidgetDiv(gridWidget* grid,lv_obj_t* parent, int width, int height){

    grid->div = lv_obj_create(parent);
    lv_obj_set_size(grid->div,width,height); 
    lv_obj_align(grid->div, LV_ALIGN_BOTTOM_MID, 0, 0);
    lv_obj_clear_flag(grid->div, LV_OBJ_FLAG_SCROLL_ELASTIC);
}

void createGridWidgetMatrix(gridWidget* grid, int rows, int columns,logicData* gameData){

    const int width = 40;
    const int height = 40;
    grid->matrix = lv_btnmatrix_create(grid->div);
    lv_obj_set_size(grid->matrix,columns*width,rows*height); 
    lv_btnmatrix_set_map(grid->matrix, (const char**)grid->displayValues);
    static lv_style_t style_bg;
    lv_style_init(&style_bg);
    lv_style_set_pad_all(&style_bg, 0);
    lv_style_set_pad_gap(&style_bg, 0);
    lv_style_set_border_width(&style_bg, 0);
    dataMatrixCallback* cbData = new dataMatrixCallback;
    cbData->gameData = gameData;
    cbData->grid = grid;
    lv_obj_add_style(grid->matrix, &style_bg, 0);
    lv_obj_add_event_cb(grid->matrix, matrixCallback, LV_EVENT_ALL, cbData);
}

void refreshGridWidgetDisplayValues(dataMatrixCallback* cbData){
    int i_data = 0;
    int j_data = 0;
    const int columns = cbData->grid->columns;
    const int rows = cbData->gameData->columns;
    int size = columns*rows+rows;
    for(int i=0; i<size-1;i++){
        
        if((i+1)%(columns+1)==0){
            i_data++;
            j_data=0;
            continue;
        }
        else if(cbData->gameData->grid[i_data][j_data].status == 1){
        //snprintf(cbData->grid->displayValues[i],sizeof(cbData->grid->displayValues[i]),"%d",cbData->gameData->grid[i_data][j_data].value);
            Serial.println(cbData->grid->displayValues[i]);
        Serial.println(cbData->gameData->grid[i_data][j_data].value);    
        Serial.println(cbData->gameData->grid[i_data][j_data].value);
        //cbData->grid->displayValues[i][0] = (const char)cbData->gameData->grid[i_data][j_data].value;
        sprintf(cbData->grid->displayValues[i],"%d",cbData->gameData->grid[i_data][j_data].value);
    
        }
        //Serial.printf("\nI:%d",i_data);
        //Serial.printf("\nJ:%d",j_data);
        j_data++;    
    }
    
}

void matrixCallback (lv_event_t * e){
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_target(e);
    dataMatrixCallback* cbData = (dataMatrixCallback*)lv_event_get_user_data(e);
    if(code == LV_EVENT_CLICKED) {
        uint32_t id = lv_btnmatrix_get_selected_btn(obj);
        if(id <= cbData->gameData->columns*cbData->gameData->rows){    
        Serial.printf("\nID:%d",id);
        const char * txt = lv_btnmatrix_get_btn_text(obj, id);
       int cols = cbData->gameData->columns;
        cords c = convertIdToCordinates(id,cols);
        Serial.println();
        Serial.println(cols);
        Serial.println(c.x);
        Serial.println(c.y);
        clickTile(c.x,c.y,cbData->gameData);
        refreshGridWidgetDisplayValues(cbData);
        }
    }
    // if(code == LV_EVENT_CLICKED) {
    //     uint32_t id = lv_btnmatrix_get_selected_btn(obj);
    //     Serial.printf("LONG: %d",id);
        
    // }
}