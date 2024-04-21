#include <Arduino.h>
#include <lvgl.h>
#include <debug.hpp>
#include <gui_grid_widget.hpp>

style_colors colors;
gui_data_matrix_callback* cbData = new gui_data_matrix_callback;

LV_FONT_DECLARE(minesweeper_font);
void gui_grid_widget_create(gui_grid_widget* grid, struct logic_data* game_data, lv_obj_t* parent) {
    grid->cols = game_data->cols;
    grid->rows = game_data->rows;
    gui_create_grid_widget_div(grid, parent, LV_HOR_RES, GRID_WIDGET_HEIGHT);
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
    
    static lv_style_t style_main;
    static lv_style_t style_items;
    static int created = 0;
    if(!created){
    lv_style_init(&style_main);
    lv_style_set_pad_all(&style_main, 0);
    lv_style_set_pad_gap(&style_main, 0);
    lv_style_set_border_width(&style_main, 0);
    lv_style_set_radius(&style_main, 0);
    }
    lv_obj_add_style(grid->matrix, &style_main, 0);
    cbData->game_data = game_data;
    cbData->grid = grid;
    if(!created){
    lv_style_init(&style_items);
    lv_style_set_radius(&style_items, 0);
    lv_style_set_border_width(&style_items, 1);
    lv_style_set_text_font(&style_items,&minesweeper_font);
    lv_style_set_bg_color(&style_items, lv_color_make(150, 150, 150));
    }
    lv_obj_add_event_cb(grid->matrix, gui_matrix_callback, LV_EVENT_ALL, cbData);
    lv_obj_add_style(grid->matrix, &style_items, LV_PART_ITEMS);
    created = 1;
}

void gui_matrix_callback(lv_event_t* e) {
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t* obj = lv_event_get_target(e);
    gui_data_matrix_callback* cbData = (gui_data_matrix_callback*)lv_event_get_user_data(e);
    
    if (code == LV_EVENT_SHORT_CLICKED) {
        uint32_t id = lv_btnmatrix_get_selected_btn(obj);
        if (id <= cbData->game_data->cols * cbData->game_data->rows) {
            //Serial.printf("\nID:%d", id);
            int cols = cbData->game_data->cols;
            cords c = help_convert_id_to_cordinates(id, cols);
            logic_click_tile_main(c.x, c.y, cbData->game_data);
            gui_refresh_grid_widget_display_values(cbData);
            Serial.printf("Short: %d", id);
            
        }
    }
    if (code == LV_EVENT_LONG_PRESSED) {
        uint32_t id = lv_btnmatrix_get_selected_btn(obj);
        if (id <= cbData->game_data->cols * cbData->game_data->rows) {
           // Serial.printf("LONG: %d", id);
            int cols = cbData->game_data->cols;
            cords c = help_convert_id_to_cordinates(id, cols);
            logic_click_flag_tile(c.x, c.y, cbData->game_data);
            gui_refresh_grid_widget_display_values(cbData);
            Serial.printf("Long: %d", id);
        }
    }

    if(code == LV_EVENT_DRAW_PART_BEGIN){
        lv_obj_draw_part_dsc_t * dsc = lv_event_get_draw_part_dsc(e);
        if(dsc->class_p == &lv_btnmatrix_class && dsc->type == LV_BTNMATRIX_DRAW_PART_BTN) {
//dsc->rect_dsc->radius = 0;
            // make every color at start
            const char* text = lv_btnmatrix_get_btn_text(obj, dsc->id);
            if(!(strcmp(text, "  ")==0) && !(strcmp(lv_btnmatrix_get_btn_text(obj, dsc->id), "`")==0)){
                dsc->rect_dsc->bg_color = colors.BACKGROUND_CLICKED;
            }
            if(text[0]=='0'){
                dsc->label_dsc->opa = 0;
            }
            if(text[0]=='1'){
                dsc->label_dsc->color = colors.LABEL_1;
            }
            else if(text[0]=='2'){
                dsc->label_dsc->color = colors.LABEL_2;
            }
            else if(text[0]=='3'){
                dsc->label_dsc->color = colors.LABEL_3;
            }
            else if(text[0]=='4'){
                dsc->label_dsc->color = colors.LABEL_4;
            }
            else if(text[0]=='5'){
                dsc->label_dsc->color = colors.LABEL_5;
            }
            else if(text[0]=='6'){
                dsc->label_dsc->color = colors.LABEL_6;
            }
            else if(text[0]=='7'){
                dsc->label_dsc->color = colors.LABEL_7;
            }
            else if(text[0]=='8'){
                dsc->label_dsc->color = colors.LABEL_8;
            }
            
        }
    }
    
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
        } 
        else if (cb_data->game_data->grid[i_data][j_data].display == TILE_DISPLAY_SHOWN) {
            sprintf(cb_data->grid->display_values[i], "%d", cb_data->game_data->grid[i_data][j_data].value);
        }

        else if (cb_data->game_data->grid[i_data][j_data].display == TILE_DISPLAY_FLAGGED) {
            sprintf(cb_data->grid->display_values[i], "`");
        }

        else if (cb_data->game_data->grid[i_data][j_data].display == TILE_DISPLAY_HIDDEN) {
            sprintf(cb_data->grid->display_values[i], "  ");
        }
        j_data++;
    }
}

void gui_grid_widget_delete(gui_grid_widget* grid){
    lv_obj_del(grid->div);
    delete grid->display_values;
}