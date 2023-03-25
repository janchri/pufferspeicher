#include "WebApi.h"
#include <AsyncJson.h>
#include "defaults.h"

WebApiClass WebApi;

WebApiClass::WebApiClass()
    : _server(HTTP_PORT)
    , _events("/events")
{
}

void WebApiClass::init()
{
    Serial.println(F("[WebApi] :  Initializing..."));
    using std::placeholders::_1;
    _server.on("/api/puffer/sensors", HTTP_GET, std::bind(&WebApiClass::onSensorsGet, this, _1));
    _server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(200, "text/plain", "Hello, world");
    });
    _server.begin();
}

void WebApiClass::loop()
{
}

void WebApiClass::onSensorsGet(AsyncWebServerRequest* request)
{
    Serial.println(F("[WebApi::onSensorsGet] :  Entering"));
    AsyncJsonResponse* response = new AsyncJsonResponse();
    JsonObject root = response->getRoot();
    root["test"]["power_set_status"] = 1234;
    response->setLength();
    request->send(response);
}