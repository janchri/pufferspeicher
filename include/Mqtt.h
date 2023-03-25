#pragma once

#include <espMqttClientAsync.h>
#include <WiFi.h>

class MqttClass {
public:
    MqttClass();
    void init();
    void loop();
    
private:
    void setup();
    espMqttClientAsync mqttClient;

    uint32_t lastTimerReconnect = 0;
    uint32_t lastTimerPublish = 0;
};

extern MqttClass Mqtt;