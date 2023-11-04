#include "Sensors.h"
#include "Logger.h"

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
        uint8_t count = 0;
        String msg = "[Sensors]:";
        for(auto address : sensor_addresses){
            sensor_data[count] = tmp_sensor.getTempC(address.data());
            count++;
            msg += tmp_sensor.getTempC(address.data());
            msg += F(" | ");
        }
        lastSensorRead = millis();
        Logger.println(msg);
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