#include "WebApi.h"
#include <AsyncJson.h>
#include "defaults.h"
#include "Sensors.h"

WebApiClass WebApi;

WebApiClass::WebApiClass()
    : _server(HTTP_PORT), _events("/events")
{
}

void WebApiClass::init()
{
    Serial.println(F("[WebApi] :  Initializing..."));
    _server.addHandler(&_events);
    using std::placeholders::_1;
    _server.on("/api/puffer", HTTP_GET, std::bind(&WebApiClass::onSensorsGet, this, _1));
    _server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
               { request->send(200, "text/plain", "Hello, world"); });
    _server.begin();
}

void WebApiClass::loop()
{
}

void WebApiClass::onSensorsGet(AsyncWebServerRequest *request)
{
    AsyncJsonResponse *response = new AsyncJsonResponse(false, 4096U);
    JsonObject root = response->getRoot();
    JsonArray sensor = root.createNestedArray(F("sensor"));

    uint8_t count = 0;
    for (auto data : Sensors.sensor_data)
    {
        JsonObject obj = sensor.createNestedObject();
        char addr[17];
        sprintf(addr, "%02X%02X%02X%02X%02X%02X%02X%02X",
                Sensors.sensor_addresses[count][0],
                Sensors.sensor_addresses[count][1],
                Sensors.sensor_addresses[count][2],
                Sensors.sensor_addresses[count][3],
                Sensors.sensor_addresses[count][4],
                Sensors.sensor_addresses[count][5],
                Sensors.sensor_addresses[count][6],
                Sensors.sensor_addresses[count][7]);
        obj[F("sensor_id")] = String(addr);
        obj[F("sensor_tmp")] = String(Sensors.sensor_data[count]);
        count++;
    }
    response->setLength();
    request->send(response);
}