#ifndef _MENUE_
#define _MENUE_

#include <lvgl.h>
#include <gui_game_difficulty_button.hpp>
#include <logic_wifi.hpp>
#include <gui_game_mode_menu.hpp>
enum gui_difficulty_menue_constants{
    GUI_DIFFICULTY_MENUE_DEFAULT,
    GUI_DIFFICULTY_MENUE_CUSTOM,
};

struct wifi_data;
struct gui_game_difficulty_button;
struct gui_game_widget;
struct gui_game_mode_menu;

struct gui_menu
{
    int page = GUI_DIFFICULTY_MENUE_DEFAULT;
    int first = 1;
    lv_obj_t* div;
    gui_game_difficulty_button* easy;
    gui_game_difficulty_button* medium;
    gui_game_difficulty_button* hard;
    gui_game_difficulty_button* custom;
    gui_game_mode_menu* mode_menu;
    gui_game_widget* master;
    lv_obj_t* back_button;
    int online_mode;
    lv_obj_t* waiting_label;
    lv_obj_t* header;

    
};

void gui_menu_create(gui_menu* menue,gui_game_widget* master, lv_obj_t* parent);

void gui_menue_create_div(gui_menu* menue, lv_obj_t* parent);

void gui_menue_create_back_button(gui_menu* menu, lv_obj_t* parent);
void gui_menue_back_button_cb(lv_event_t* e);

void gui_menue_item_show(lv_obj_t* object);
void gui_menue_item_hide(lv_obj_t* object);


void gui_menue_next_page_button_cb(lv_event_cb_t* e);

void gui_menu_singleplayer(gui_menu* menu);
void gui_menu_multiplayer(gui_menu* menu);


void gui_menu_waiting_create(gui_menu* menue, lv_obj_t* parent);

void gui_menu_header_create(gui_menu* menue, lv_obj_t* parent);
void gui_menu_header_style_init(lv_obj_t* header);

void gui_menu_waiting_style_init(lv_obj_t* waiting_label);

void gui_menu_slave_receive_difficulty(wifi_data data);
#endif