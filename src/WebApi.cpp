#include "WebApi.h"
#include "defaults.h"
#include "Logger.h"
#include "Sensors.h"
#include <AsyncElegantOTA.h>

WebApiClass WebApi;

WebApiClass::WebApiClass()
    : _server(HTTP_PORT), _ws("/ws")
{
}

void onWsEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len)
{
    if (type == WS_EVT_CONNECT)
    {
        Logger.println(F("[WebApi]: Websocket client connection received"));
        client->text(F("[WebApi]: Hello from Puffer"));
    }
    else if (type == WS_EVT_DISCONNECT)
    {
        Logger.println(F("[WebApi]: Client disconnected"));
    }
}

void WebApiClass::init()
{
    Logger.println(F("[WebApi] :  Initializing..."));
    AsyncElegantOTA.begin(&_server); 
    _ws.onEvent(onWsEvent);
    _server.addHandler(&_ws);
    using std::placeholders::_1;
    _server.on("/api/puffer", HTTP_GET, std::bind(&WebApiClass::onSensorsGet, this, _1));

    _server.serveStatic("/", LittleFS, "/").setDefaultFile("index.html");

    _server.begin();
}

void WebApiClass::loop()
{
    if (_ws.count() == 0)
    {
        return;
    }
    if (millis() - _lastWsCleanup > WS_TIMEOUT_PUBLISH*0.3)
    {
        _ws.cleanupClients();
        _lastWsCleanup = millis();
    }
    if (millis() - _lastWsPublish > WS_TIMEOUT_PUBLISH)
    {
        DynamicJsonDocument root(1024U);
        JsonVariant var = root;
        generateJsonResponse(var);
        String buffer;
        if (buffer)
        {
            serializeJson(root, buffer);
            _ws.textAll(buffer);
        }
        _lastWsPublish = millis();
    }
}

void WebApiClass::onSensorsGet(AsyncWebServerRequest *request)
{
    AsyncJsonResponse *response = new AsyncJsonResponse(false, 1024U);
    JsonVariant root = response->getRoot();

    generateJsonResponse(root);

    response->setLength();
    request->send(response);
}

void WebApiClass::generateJsonResponse(JsonVariant &root)
{
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
}