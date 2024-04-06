#include <lvgl.h>
#include <TFT_eSPI.h>
#include <Arduino.h>
#include <lvglMasterSetup.hpp>
#include <logic.hpp>
#include <debug.hpp>
#include <gui_game_widget.hpp>
#include <logic_game_difficulty.hpp>
#include <gui_game_difficulty_button.hpp>
#include <gui_menue.hpp>

gui_menue testMenue;
gui_game_widget test;

void setup()
{ 
   lvgl_master_init();
  gui_menue_create(&testMenue, &test, lv_scr_act());

}

void loop()
{
  lv_timer_handler();
  if(test.started){ 
    gui_timer_widget_refresh(test.master_timer);
    gui_mine_counter_widget_refresh(test.master_counter, test.master_grid_data); 
  }
  delay( 10 );
}