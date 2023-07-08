
#ifndef defines_h
#define defines_h

#if (ESP8266)
  #define BOARD_TYPE      "ESP8266"
#else
  #error This code is intended to run only on the ESP8266 boards ! Please check your Tools->Board setting.
#endif

#ifndef BOARD_NAME
  #define BOARD_NAME    BOARD_TYPE
#endif

#define DEBUG_WEBSOCKETS_PORT     Serial
// Debug Level from 0 to 4
#define _WEBSOCKETS_LOGLEVEL_     4

const char* ssid = "D-Link"; //Enter SSID
const char* password = "cusat#1234"; //Enter Password

//const char* websockets_server_host = "192.168.2.95"; //Enter server address
const char* websockets_server_host = "172.16.148.112"; //Enter server address
//const char* websockets_server_host = "serverip_or_name"; //Enter server address

#define WEBSOCKETS_PORT   8000    //8080

const uint16_t websockets_server_port = WEBSOCKETS_PORT; // Enter server port

#endif 