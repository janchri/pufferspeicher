#pragma once

#include <Arduino.h>
#include "LittleFS.h"

#define SERIAL_BAUDRATE 115200

#define ONE_WIRE_BUS 14
#define NUMBER_OF_TMP_SENSORS 10

#define HOSTNAME "Puffer"

#define WIFI_SSID ""
#define WIFI_PASSWORD ""
#define WIFI_TIMEOUT_RECONNECT 10000

#define AP_SSID "Puffer"
#define AP_PASSWORD ""
#define AP_TIMEOUT 200

#define MQTT_TIMEOUT_PUBLISH 5000
#define MQTT_TIMEOUT_RECONNECT 5000
#define MQTT_SERVER "192.168.178.67"
#define MQTT_PORT 1883
#define MQTT_USER ""
#define MQTT_PASSWORD ""
#define MQTT_RETAIN 0

#define HTTP_PORT 80

#define SENSORS_TIMEOUT_READ 5000
#define SENSORS_TIMEOUT_SEARCH 100000

#define WS_TIMEOUT_PUBLISH 60000

