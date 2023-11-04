#include "Mqtt.h"
#include "Network.h"
#include "Sensors.h"
#include "Logger.h"
#include "defaults.h"
#include "credentials.h"

MqttClass Mqtt;
WiFiClient wiFiClient;

MqttClass::MqttClass()
{
}

void MqttClass::init()
{
    mqttClient.setServer(MQTT_SERVER, MQTT_PORT);
    mqttClient.setCredentials(MQTT_USER,MQTT_PASSWORD);
    mqttClient.setClientId(HOSTNAME);
    setup();
}

void MqttClass::setup()
{
    if (Network.isConnected())
    {
        Logger.println("[MQTT]: Connecting to MQTT...");
        if (!mqttClient.connect())
        {
            Logger.println("[MQTT]: Connecting failed.");
        }
        else
        {
            Logger.println("[MQTT]: Connected.");
        }
    }
    else
    {
        Logger.println("[MQTT]: Error no WiFi Connection");
    }
}

void MqttClass::loop()
{
    if ((millis() - lastTimerReconnect) > MQTT_TIMEOUT_RECONNECT)
    {
        if (!mqttClient.connected())
        {
            Logger.println(F("[MQTT] : Not connected."));
            setup();
        }
        else
        {
            Logger.println(F("[MQTT] : Connected."));
        }
        lastTimerReconnect = millis();
    }
    if ((millis() - lastTimerPublish) > MQTT_TIMEOUT_PUBLISH)
    {
        Logger.println(F("[MQTT]: Publish data"));
        uint8_t count = 0;
        for (auto data : Sensors.sensor_data)
        {
            String topic = HOSTNAME;
            topic += "/sensor/";
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
            topic += String(addr);
            mqttClient.publish(topic.c_str(), 0, true, String(Sensors.sensor_data[count]).c_str());
            count++;
        }

        lastTimerPublish = millis();
    }
}