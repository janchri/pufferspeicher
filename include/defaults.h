#pragma once

#include <Arduino.h>
#include "LittleFS.h"

#define SERIAL_BAUDRATE 115200

#define ONE_WIRE_BUS 14
#define NUMBER_OF_TMP_SENSORS 10

#define HOSTNAME "Puffer"
#define WIFI_TIMEOUT_CHECK_STATUS_MS 499u*1000u

#define AP_SSID "Puffer"
#define AP_PASSWORD ""
#define AP_TIMEOUT 5000u

#define MQTT_TIMEOUT_PUBLISH 30u*1000u
#define MQTT_TIMEOUT_RECONNECT 60u*1000u
#define MQTT_PORT 1883
#define MQTT_RETAIN 0

#define HTTP_PORT 80

#define SENSORS_TIMEOUT_READ 60u*1000u
#define SENSORS_TIMEOUT_SEARCH 300000u

#define WS_TIMEOUT_PUBLISH 15u*1000u

#define NTP_SERVER_0 "at.pool.ntp.org"
#define NTP_SERVER_1 "at.pool.ntp.org"
#define NTP_SERVER_2 "at.pool.ntp.org"
#define MY_TZ "CET-1CEST,M3.5.0/02,M10.5.0/03"

