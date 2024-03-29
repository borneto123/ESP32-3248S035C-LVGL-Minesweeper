#include <Arduino.h>
#include <lvgl.h>

#include <debug.hpp>
#include <gui.hpp>

void gui_create_grid_widget(gui_grid_widget* grid, struct logic_data* game_data, lv_obj_t* parent) {
    grid->cols = game_data->cols;
    grid->rows = game_data->rows;
    gui_create_grid_widget_div(grid, parent, LV_HOR_RES, GRID_WIDGET_WIDTH);
    gui_create_grid_widget_display_values(grid, game_data->rows, game_data->cols);
    gui_create_grid_widget_matrix(grid, game_data->rows, game_data->cols, game_data);
}

void gui_create_grid_widget_div(gui_grid_widget* grid, lv_obj_t* parent, int width, int height) {
    grid->div = lv_obj_create(parent);
    lv_obj_set_size(grid->div, width, height);
    lv_obj_align(grid->div, LV_ALIGN_BOTTOM_MID, 0, 0);
    lv_obj_clear_flag(grid->div, LV_OBJ_FLAG_SCROLL_ELASTIC);
}

void gui_create_grid_widget_display_values(gui_grid_widget* grid, int rows, int cols) {
    int mapSize = cols * rows + rows;
    grid->display_values = new char*[mapSize];
    for (int i = 0; i < mapSize - 1; i++) {
        grid->display_values[i] = new char[3];
        if ((i + 1) % (cols + 1) == 0)
            sprintf(grid->display_values[i], "\n");
        else
            sprintf(grid->display_values[i], "  ");
    }
    grid->display_values[mapSize - 1] = NULL;
}

void gui_create_grid_widget_matrix(gui_grid_widget* grid, int rows, int cols, logic_data* game_data) {
    grid->matrix = lv_btnmatrix_create(grid->div);
    lv_obj_set_size(grid->matrix, cols * GRID_TILE_WIDTH, rows * GRID_TILE_HEIGHT);
    lv_btnmatrix_set_map(grid->matrix, (const char**)grid->display_values);
    static lv_style_t style_bg;
    lv_style_init(&style_bg);
    lv_style_set_pad_all(&style_bg, 0);
    lv_style_set_pad_gap(&style_bg, 0);
    lv_style_set_border_width(&style_bg, 0);
    gui_data_matrix_callback* cbData = new gui_data_matrix_callback;
    cbData->game_data = game_data;
    cbData->grid = grid;
    lv_obj_add_style(grid->matrix, &style_bg, 0);
    lv_obj_add_event_cb(grid->matrix, gui_matrix_callback, LV_EVENT_ALL, cbData);
}

void gui_refresh_grid_widget_display_values(gui_data_matrix_callback* cb_data) {
    int i_data = 0;
    int j_data = 0;
    const int columns = cb_data->grid->cols;
    const int rows = cb_data->game_data->cols;
    int size = columns * rows + rows;
    for (int i = 0; i < size - 1; i++) {
        if ((i + 1) % (columns + 1) == 0) {
            i_data++;
            j_data = 0;
            continue;
        } else if (cb_data->game_data->grid[i_data][j_data].display == 1) {
            sprintf(cb_data->grid->display_values[i], "%d", cb_data->game_data->grid[i_data][j_data].value);
        }
        j_data++;
    }
}

void gui_matrix_callback(lv_event_t* e) {
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t* obj = lv_event_get_target(e);
    gui_data_matrix_callback* cbData = (gui_data_matrix_callback*)lv_event_get_user_data(e);
    if (code == LV_EVENT_CLICKED) {
        uint32_t id = lv_btnmatrix_get_selected_btn(obj);
        if (id <= cbData->game_data->cols * cbData->game_data->rows) {
            Serial.printf("\nID:%d", id);
            const char* txt = lv_btnmatrix_get_btn_text(obj, id);
            int cols = cbData->game_data->cols;
            cords c = help_convert_id_to_cordinates(id, cols);
            logic_click_tile_main(c.x, c.y, cbData->game_data);
            gui_refresh_grid_widget_display_values(cbData);
        }
    }
    // if(code == LV_EVENT_CLICKED) {
    //     uint32_t id = lv_btnmatrix_get_selected_btn(obj);
    //     Serial.printf("LONG: %d",id);

    // }
}