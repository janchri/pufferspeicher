#include "Sensors.h"

SensorsClass Sensors;
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature tmp_sensor(&oneWire);

SensorsClass::SensorsClass()
{
}

void SensorsClass::init()
{
    findSensors();
}

void SensorsClass::setup()
{
}

void SensorsClass::loop()
{
    if ((millis() - lastSensorRead) > SENSORS_TIMEOUT_READ)
    {
        tmp_sensor.requestTemperatures();
        Serial.print(F("[Sensors] : "));
        uint8_t count = 0;
        for(auto address : sensor_addresses){
            Serial.print(tmp_sensor.getTempC(address.data()));
            Serial.print(F(" | "));
            sensor_data[count] = tmp_sensor.getTempC(address.data());
            count++;
        }
        Serial.println();
        lastSensorRead = millis();
    }
    if ((millis() - lastSensorSearch) > SENSORS_TIMEOUT_SEARCH)
    {
        findSensors();
        lastSensorSearch = millis();
    }
}

void SensorsClass::findSensors()
{
    std::array<uint8_t, 8> address;
    uint8_t count = 0;

    while (oneWire.search(address.data()) && count < sensor_addresses.size()) {
        sensor_addresses[count] = address;
        count++;
    }    
    oneWire.reset_search();
}