#include <lvgl.h>
#include <TFT_eSPI.h>
#include <Arduino.h>
#include <lvglMasterSetup.hpp>
#include <logic.hpp>
#include <debug.hpp>
#include <gui_grid_widget.hpp>
#include <gui_timer_widget.hpp>
logic_data gameDataTest; 
gui_grid_widget gridTest;
gui_timer_widget timerTest;
static void btn_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * btn = lv_event_get_target(e);
    if(code == LV_EVENT_CLICKED) {
      lv_obj_del(btn);
        gameDataTest = logic_create_logic_data(20,20);
        logic_generate_level(100,&gameDataTest);
        gui_create_grid_widget(&gridTest,&gameDataTest,lv_scr_act());
        debug_print_grid_value(gameDataTest);
          gui_timer_widget_create(&timerTest, lv_scr_act());
  gui_timer_widget_start(&timerTest);
    }
}

/**
 * Create a button with a label and react on click event.
 */
void starBtn(void)
{
    lv_obj_t * btn = lv_btn_create(lv_scr_act());     /*Add a button the current screen*/
    lv_obj_set_pos(btn, 10, 10);                            /*Set its position*/
    lv_obj_set_size(btn, 120, 50);                          /*Set its size*/
    lv_obj_add_event_cb(btn, btn_event_cb, LV_EVENT_ALL, NULL);           /*Assign a callback to the button*/

    lv_obj_t * label = lv_label_create(btn);          /*Add a label to the button*/
    lv_label_set_text(label, "Start");                     /*Set the labels text*/
    lv_obj_center(label);
}

void setup()
{ 
  lvgl_master_init();
  starBtn();

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
  gui_timer_widget_refresh(&timerTest);
  delay( 10 );
}