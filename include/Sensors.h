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
    std::array<float,NUMBER_OF_TMP_SENSORS> sensor_data;
    std::array<std::array<uint8_t, 8>, NUMBER_OF_TMP_SENSORS> sensor_addresses;
    
private:
    void setup();
    uint32_t lastSensorRead = SENSORS_TIMEOUT_READ + 1;
    uint32_t lastSensorSearch = 0;
};

extern SensorsClass Sensors;