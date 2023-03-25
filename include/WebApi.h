#pragma once

#include <ESPAsyncWebServer.h>

class WebApiClass {
public:
    WebApiClass();
    void init();
    void loop();
    
private:
    AsyncWebServer _server;
    AsyncEventSource _events;
    void onSensorsGet(AsyncWebServerRequest* request);
};

extern WebApiClass WebApi;