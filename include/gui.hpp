#ifndef _GUI_
#define _GUI_
#include <lvgl.h>
#include <logic.hpp>
#include <help.hpp>

enum gui_grid_widget_constants{
    GRID_WIDGET_WIDTH = 400,
    GRID_TILE_WIDTH = 40,
    GRID_TILE_HEIGHT = 40,
};

/**
 * This struct stores information about widget that has all minesweeper logic:
 * - `div` pointer to button matrix parent
 * - `matrix` pointer to button matrix lv object
 * - `display_values` 2d array that has all display values
 * - `rows` number of rows in grid
 * - `cols` number of columns in grid
 */
struct gui_grid_widget{
    lv_obj_t* div;
    lv_obj_t* matrix;
    char** display_values;
    int rows;
    int cols;
};

/**
 *   This struct stores wraps gui_grid_widget and logic_data struct so they can be transpored to
 *   data matrix callback
 * - `grid` pointer to gui_grid_widget struct
 * - `game_data` pointer to logic_data struct
 * 
 */
struct gui_data_matrix_callback{
    gui_grid_widget* grid;
     logic_data* game_data;
};

/**
 * @brief Function that creates widget with game_data and pointer to parent element
 * 
 * @param grid gui_grid_widget* struct
 * @param game_data logic_data* struct
 * @param parent pointer to parent of grid widget
 */
void gui_create_grid_widget(gui_grid_widget* grid, logic_data* game_data,lv_obj_t* parent);


/**
 * @brief Function that creates a parent of button matrix
 * 
 * @param grid gui_grid_widget*
 * @param parent pointer to parent of grid widget
 * @param width width of div
 * @param height height of div
 */
void gui_create_grid_widget_div(gui_grid_widget* grid,lv_obj_t* parent, int width, int height);

/**
 * @brief Function that creates values that will be put on matrix buttons
 * 
 * @param grid gui_grid_widget* 
 * @param rows number of rows in grid
 * @param cols number of columns in grid
 */
void gui_create_grid_widget_display_values(gui_grid_widget* grid, int rows, int cols);

/**
 * @brief Function that creates button matrix in gui_grid_widget
 * 
 * @param grid gui_grid_widget*
 * @param rows number of rows in grid
 * @param cols number of columns in grid
 * @param game_data logic_data* 
 */
void gui_create_grid_widget_matrix(gui_grid_widget* grid, int rows, int cols,logic_data* game_data);

/**
 * @brief function that refreshes dislay_values on button matrix
 * 
 * @param cb_data gui_data_matrix_callback*
 */
void gui_refresh_grid_widget_display_values(gui_data_matrix_callback* cb_data);


/**
 * @brief Function that is used as callback to handle events for button matrix
 * 
 * @param e lv_event_t *
 */
void gui_matrix_callback (lv_event_t * e);

#endif