#include <lvgl.h>
#include <TFT_eSPI.h>
#include <Arduino.h>
#include <lvglMasterSetup.hpp>
#include <logic.hpp>
#include <logic_debug.hpp>
logicData gameDataTest; 

void setup()
{ 
  lvgl_master_init();
  gameDataTest = createLogicData(10,10);

  generateLevel(10,&gameDataTest);
  printGridValue(gameDataTest);

}


void loop()
{
     

  //lvgl timer logic 
  lv_timer_handler(); 
  delay( 10 );
}