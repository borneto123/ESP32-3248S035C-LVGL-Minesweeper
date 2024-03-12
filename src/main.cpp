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

  

}


void loop()
{
     
if(millis() >2000 && millis()<2020){
  generateLevel(10,&gameDataTest);
  printGridValue(gameDataTest);
  Serial.println();
  clickTile(9,0,&gameDataTest);
  clickTile(9,5,&gameDataTest);
  clickFlagBombTile(0,0,&gameDataTest);
  printGridStatus(gameDataTest);
  Serial.println();
  printUserPerspective(gameDataTest);
}

  //lvgl timer logic 
  lv_timer_handler(); 
  delay( 10 );
}