#pragma once

#include <AsyncJson.h>
#include <ArduinoJson.h>
#include <ESPAsyncWebServer.h>

class WebApiClass {
public:
    WebApiClass();
    void init();
    void loop();
    
private:
    uint32_t _lastWsCleanup = 0;
    uint32_t _lastWsPublish = 0;
    AsyncWebServer _server;
    AsyncWebSocket _ws;
    void onSensorsGet(AsyncWebServerRequest* request);
    void generateJsonResponse(JsonVariant& root);
};

extern WebApiClass WebApi;