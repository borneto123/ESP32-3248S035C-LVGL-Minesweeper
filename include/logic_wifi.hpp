#ifndef _WIFI_
#define _WIFI_
#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>
#include <logic_game_difficulty.hpp>
#include <logic_game_difficulty.hpp>
#include <gui_menu.hpp>
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
// Mac addresses of devices
extern uint8_t mac[2][6];
extern String mac_str[2];

/**
 * This struct stores packet information:
 * - `type` type of packet
 * - `difficulty` value of difficulty
 * - `end_game_data` value of end game_data
 * - `test` variable used for test
 */
struct wifi_packet{
    uint8_t type; 
    logic_game_difficulty difficulty;
    logic_end_game_data end_game_data;
    int test;
};

/**
 * This struct stores esp_now information:
 * - `send` latest sent packet
 * - `receive` latest received packets
 * - `peer_info` esp_now_peer_info_t
 * - `menu` pointer to gui_menu
 */
struct wifi_data{
    wifi_packet send;
    wifi_packet receive;
    esp_now_peer_info_t peer_info;
    gui_menu* menu;
};

/**
 * @brief Function that starts wifi if not needed
 */
void wifi_mode_smart();

/**
 * @brief Function that determines if the device is a slave or master
 * @return 
 */
int wifi_device_type();

/**
 * @brief Function that prints the MAC address of the device
 */
void wifi_print_mac();

/**
 * @brief Function that starts esp_now
 * @param menu 
 */
void wifi_init(gui_menu* menu);

/**
 * @brief Callback function that is called when data is sent
 * @param mac_addr mac address
 * @param status status
 */
void wifi_on_data_sent(const uint8_t *mac_addr, esp_now_send_status_t status);

/**
 * @brief Callback function that is called when data is received
 * @param mac mac address
 * @param incomingData data
 * @param len length
 */
void wifi_on_data_recv(const uint8_t * mac, const uint8_t *incomingData, int len);

/**
 * @brief Function that handles received data
 */
void wifi_handle_new_data();

/**
 * @brief Function that sends data
 */
void wifi_send_data();

/**
 * @brief Function used for testing communication
 */
void wifi_send_test();

/**
 * @brief Function that sends difficulty to slave
 */
void wifi_send_difficulty(logic_game_difficulty difficulty);

/**
 * @brief Function that sends slave result to the master
 */
void wifi_send_result_slave(logic_end_game_data logic_end_game_data);

/**
 * @brief Function that final result to slave
 */
void wifi_send_result_finale(logic_end_game_data logic_end_game_data);
#endif 