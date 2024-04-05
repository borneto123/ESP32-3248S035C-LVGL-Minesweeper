#include <lvgl.h>
#include <TFT_eSPI.h>
#include <Arduino.h>
#include <lvglMasterSetup.hpp>
#include <logic.hpp>
#include <debug.hpp>
#include <gui_game_widget.hpp>
#include <logic_game_difficulty.hpp>
#include <gui_game_difficulty_button.hpp>
logic_data gameDataTest; 
gui_grid_widget gridTest;
gui_timer_widget timerTest;
gui_mine_counter_widget counterTest;

logic_game_difficulty gameEasyTest;
logic_game_difficulty gameMediumTest;
logic_game_difficulty gameHardTest;



gui_game_difficulty_button buttonEasyTest;
gui_game_difficulty_button buttonMediumTest;
gui_game_difficulty_button buttonHardTest;

gui_game_widget test;
int refresh = 0;
/*
static void btn_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * btn = lv_event_get_target(e);
    if(code == LV_EVENT_CLICKED) {
       lv_obj_del(btn);
        logic_create_logic_data(&gameDataTest,10,10,10);
        gui_grid_widget_create(&gridTest,&gameDataTest,lv_scr_act());
        debug_print_grid_value(gameDataTest);
        gui_timer_widget_create(&timerTest, lv_scr_act());
        gui_timer_widget_start(&timerTest);
        gui_mine_counter_widget_create(&counterTest,&gameDataTest,lv_scr_act());
      lv_obj_del(btn);
        refresh = 1; 
        gui_game_widget_create(&test, gameTest, lv_scr_act());
    }
}*/

/**
 * Create a button with a label and react on click event.
 */
/*void starBtn(void)
{
     lv_obj_t * btn = lv_btn_create(lv_scr_act());     
    lv_obj_set_pos(btn, 10, 10);                            
    lv_obj_set_size(btn, 120, 50);                          
    lv_obj_add_event_cb(btn, btn_event_cb, LV_EVENT_ALL, NULL);           

    lv_obj_t * label = lv_label_create(btn);          
    lv_label_set_text(label, "Start");                     
    lv_obj_center(label);
}
 */
void setup()
{ 
  lvgl_master_init();
  logic_game_difficulty_create(&gameEasyTest, 9, 9, 10);
  logic_game_difficulty_create(&gameMediumTest, 14, 14, 40);
  logic_game_difficulty_create(&gameHardTest, 20, 20, 99);
 //starBtn();
  gui_game_difficulty_button_create(&test,&buttonEasyTest, &gameEasyTest, "Easy", lv_color_black(),lv_color_white(),lv_scr_act());
  gui_game_difficulty_button_create(&test,&buttonMediumTest, &gameMediumTest, "Medium", lv_color_black(),lv_color_white(),lv_scr_act());
  gui_game_difficulty_button_create(&test,&buttonHardTest, &gameHardTest, "Hard", lv_color_black(),lv_color_white(),lv_scr_act());
}

void loop()
{
     
if(millis() >2000 && millis()<2020){
//   generateLevel(10,&gameDataTest);
//   debug_print_grid_value(gameDataTest);
//   Serial.println();
//   logic_click_tile_main(9,0,&gameDataTest);
//   logic_click_tile_main(9,5,&gameDataTest);
//   logic_click_flag_tile(0,0,&gameDataTest);
//   debug_print_grid_display(gameDataTest);
//   Serial.println();
//   debug_print_user_perspective(gameDataTest);
//  testBody(LV_HOR_RES,400,lv_scr_act());
  //lv_example_btnmatrix_2();
  //testMatrix(10,10,lv_scr_act());
 // gridTest.display_values[5]="A";
}

  //lvgl timer logic 
  lv_timer_handler();
  if(test.started){ 
    gui_timer_widget_refresh(test.master_timer);
    gui_mine_counter_widget_refresh(test.master_counter, test.master_grid_data); 
  }
  delay( 10 );
}