#pragma once

#include <OneWire.h>
#include <DallasTemperature.h>
#include <vector>

#include "defaults.h"

class SensorsClass {
public:
    SensorsClass();
    void init();
    void loop();
    void findSensors();
    
private:
    void setup();
    uint32_t lastSensorRead = 0;
    uint32_t lastSensorSearch = 0;
    std::array<std::array<uint8_t, 8>, NUMBER_OF_TMP_SENSORS> sensor_addresses;
};

extern SensorsClass Sensors;