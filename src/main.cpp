#include <lvgl.h>
#include <TFT_eSPI.h>
#include <Arduino.h>
#include <lvglMasterSetup.hpp>
#include <logic.hpp>
#include <debug.hpp>
#include <gui_game_widget.hpp>
#include <logic_game_difficulty.hpp>
#include <gui_game_difficulty_button.hpp>
#include <gui_menu.hpp>
#include <logic_wifi.hpp>
#include <gui_game_mode_menu.hpp>
gui_menu testMenue;
gui_game_widget test;
gui_game_mode_menu test_mode;
void setup()
{ 
	
	lvgl_master_init();
	gui_menu_create(&testMenue, &test, lv_scr_act());
	gui_game_mode_menu_create(&test_mode, lv_scr_act(), &testMenue);
	Serial.begin(115200);
	WiFi.mode(WIFI_MODE_STA);
	//wifi_init(&testMenue);

}
bool send = false;
void loop()
{
	 
	if(test.started){ 
		gui_timer_widget_refresh(test.master_timer);
		gui_mine_counter_widget_refresh(test.master_counter, test.master_grid_data);
		
	
	}
	
	
	lv_timer_handler(); /*/*Process timers, events, animations, display refreshed, and input devices*/
	
	delay( 10 );
}