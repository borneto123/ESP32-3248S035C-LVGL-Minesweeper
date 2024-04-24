#include <logic_wifi.hpp>


uint8_t mac[2][6] = {
    {0xB8, 0xD6, 0x1A, 0x81, 0xC4, 0x40},
    {0xC0, 0x49, 0xEF, 0x11, 0xEB, 0x08}
};

String mac_str[2] = {"B8:D6:1A:81:C4:40", "C0:49:EF:11:EB:08"};

wifi_data device;

void wifi_mode_smart(){
    if(WiFi.getMode() != WIFI_MODE_STA)
        WiFi.mode(WIFI_MODE_STA);
}

void wifi_print_mac(){

    wifi_mode_smart();
    Serial.printf("\nMac address: %s",WiFi.macAddress().c_str());
}


int wifi_device_type(){
    wifi_mode_smart();
    if(WiFi.macAddress() == mac_str[WIFI_DEVICE_MASTER]) return WIFI_DEVICE_MASTER;
    else if(WiFi.macAddress() == mac_str[WIFI_DEVICE_SLAVE]) return WIFI_DEVICE_SLAVE;
}

void wifi_init(gui_menu* menu){
    Serial.println("Starting wifi");
    device.menu = menu;
    int dev_type = wifi_device_type();
    int peer_type = !dev_type;
    if (esp_now_init() != ESP_OK) {
        Serial.println("Error initializing ESP-NOW");
        return;
    }
    Serial.println("Started esp_now");
    esp_now_register_send_cb(wifi_on_data_sent);
    memcpy(device.peer_info.peer_addr, mac[peer_type],6);
    device.peer_info.channel = 0;
    device.peer_info.encrypt = false;

    do{
      Serial.println("Adding peer failed");
      esp_now_add_peer(&device.peer_info);
    }while( !esp_now_is_peer_exist(mac[peer_type]));
    Serial.println("Added peer");
    esp_now_register_recv_cb(wifi_on_data_recv);
}

void wifi_on_data_sent(const uint8_t *mac_addr, esp_now_send_status_t status){
    Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
  if (status ==0){
    Serial.println("Delivery Success");
  }
  else{
    Serial.println("Delivery Fail");
  }
}

void wifi_on_data_recv(const uint8_t * mac, const uint8_t *incomingData, int len){
   
   memcpy(&device.receive, incomingData, sizeof(device.receive));
   Serial.print("Bytes received: ");
   Serial.println(len);
   wifi_handle_new_data();
}

void wifi_handle_new_data(){
  if(device.menu->online_mode){
    if(device.receive.type == WIFI_PACKET_DIFFICULTY){
        Serial.println("Primljen difficulty");
        gui_menu_slave_receive_difficulty(device);
    }
    if(device.receive.type == WIFI_PACKET_SLAVE_END){
        Serial.println("Primljen slave result");
        logic_data_master_send_final(device);
    }
    if(device.receive.type == WIFI_PACKET_FINALE_RESULT){
        Serial.println("Primljen finale result");
        logic_data_handle_slave_receive_final(device);
    }
    if(device.receive.type == WIFI_PACKET_SHORT_CLICK){
        Serial.println("Primljen short click");
        logic_click_tile_main(device.receive.c.x, device.receive.c.y, device.menu->master->master_grid_data,LOGIC_DATA_CLICK_PACKET);
    }
  }
}

void wifi_send_data(){
    esp_err_t result = esp_now_send(device.peer_info.peer_addr, (uint8_t *) &device.send, sizeof(device.send));
    
  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }
}

void wifi_send_test(){

    device.send.type = WIFI_PACKET_TEST;
    device.send.test = 23;
    wifi_send_data(); 
}

void wifi_send_result_slave(logic_end_game_data logic_end_game_data){
    Serial.println("----SLAVE:WIFI_PACKET_SLAVE_END");
    Serial.printf("\nState: %d", logic_end_game_data.state);
    Serial.println("\n------------------------------------");
    device.send.type = WIFI_PACKET_SLAVE_END;
    device.send.end_game_data = logic_end_game_data;
    device.send.end_game_data.type = WIFI_PACKET_SLAVE_END;
    wifi_send_data();
}

void wifi_send_difficulty(logic_game_difficulty difficulty){
    device.send.type = WIFI_PACKET_DIFFICULTY;
    device.send.difficulty = difficulty;
    device.send.end_game_data.type = WIFI_PACKET_DIFFICULTY;
    wifi_send_data();
}

void wifi_send_result_finale(logic_end_game_data logic_end_game_data){
      device.send.type = WIFI_PACKET_FINALE_RESULT;
      device.send.end_game_data = logic_end_game_data;
      device.send.end_game_data.type = WIFI_PACKET_FINALE_RESULT;
      wifi_send_data();
}

void wifi_send_click_short(cords cords){
  Serial.println("Saljem click");
  device.send.type = WIFI_PACKET_SHORT_CLICK;
  device.send.c = cords;
  wifi_send_data();
}