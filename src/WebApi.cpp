#include "WebApi.h"
#include "defaults.h"
#include "Sensors.h"

WebApiClass WebApi;

WebApiClass::WebApiClass()
    : _server(HTTP_PORT), _ws("/ws")
{
}

void onWsEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len)
{
    if (type == WS_EVT_CONNECT)
    {
        Serial.println("Websocket client connection received");
        client->text("Hello from Puffer");
    }
    else if (type == WS_EVT_DISCONNECT)
    {
        Serial.println("Client disconnected");
    }
}

void WebApiClass::init()
{
    Serial.println(F("[WebApi] :  Initializing..."));
    _ws.onEvent(onWsEvent);
    _server.addHandler(&_ws);
    using std::placeholders::_1;
    _server.on("/api/puffer", HTTP_GET, std::bind(&WebApiClass::onSensorsGet, this, _1));
    _server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
               { request->send(200, "text/plain", "Hello, world"); });
    _server.begin();
}

void WebApiClass::loop()
{
    if (millis() - _lastWsCleanup > 1000) {
        _ws.cleanupClients();
        _lastWsCleanup = millis();
    }
    if (_ws.count() == 0) {
        return;
    }
    if (millis() - _lastWsPublish > WS_TIMEOUT_PUBLISH)
    {
        DynamicJsonDocument root(4096);
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
    AsyncJsonResponse *response = new AsyncJsonResponse(false, 4096U);
    JsonVariant root = response->getRoot();

    generateJsonResponse(root);

    response->setLength();
    request->send(response);
}

void WebApiClass::generateJsonResponse(JsonVariant& root){
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