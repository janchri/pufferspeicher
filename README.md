Simple WebServer + MQTT Client, publishes the temperature data of 10 DS18B20 sensors to a MQTT Broker and shows a website with all the data;

One has to create an own "credential.h" file in the "include" directory containing all the sensitive data. For example:

#pragma once

#define WIFI_SSID "FRITZ!Box 7590 HC"
#define WIFI_PASSWORD "123456789"

#define MQTT_SERVER "192.168.178.23"
#define MQTT_USER ""
#define MQTT_PASSWORD ""