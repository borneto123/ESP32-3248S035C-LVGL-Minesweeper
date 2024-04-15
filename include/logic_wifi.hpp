#ifndef _WIFI_
#define _WIFI_
#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>
#include <logic_game_difficulty.hpp>
#include <logic_game_difficulty.hpp>
#include <gui_menue.hpp>
#include <logic_end_game_data.hpp>
struct gui_menu;
struct logic_data;

enum wifi_device_type{
    WIFI_DEVICE_MASTER,
    WIFI_DEVICE_SLAVE,
};

enum wifi_packet_type{
    WIFI_PACKET_TEST,
    WIFI_PACKET_DIFFICULTY,
    WIFI_PACKET_SLAVE_END,
    WIFI_PACKET_FINALE_RESULT,
};

extern uint8_t mac[2][6];
extern String mac_str[2];

struct wifi_packet{
    uint8_t type; // 0 - logic // 1-lost // 2-win //-1- test
    logic_game_difficulty difficulty;
    logic_end_game_data end_game_data;
    int test;
};

struct wifi_data{
    wifi_packet send;
    wifi_packet receive;
    esp_now_peer_info_t peer_info;
    gui_menu* menu;
};

// Return enum with Master or Slave
void wifi_mode_smart();

int wifi_device_type();

void wifi_print_mac();

void wifi_init(gui_menu* menu);

void wifi_on_data_sent(const uint8_t *mac_addr, esp_now_send_status_t status);

void wifi_on_data_recv(const uint8_t * mac, const uint8_t *incomingData, int len);

void wifi_handle_new_data();

void wifi_send_data();

void wifi_send_test();

void wifi_send_difficulty(logic_game_difficulty difficulty);
void wifi_send_result_slave(logic_end_game_data logic_end_game_data);

void wifi_send_result_finale(logic_end_game_data logic_end_game_data);
#endif 