#include "Mqtt.h"
#include "Network.h"
#include "defaults.h"

MqttClass Mqtt;
WiFiClient wiFiClient;

MqttClass::MqttClass()
{
}

void MqttClass::init()
{
    mqttClient = PubSubClient(wiFiClient);
    setup();
}

void MqttClass::setup()
{
    if (Network.isConnected())
    {
        mqttClient.setServer(MQTT_SERVER, MQTT_PORT);
        if (mqttClient.connect(HOSTNAME, MQTT_USER, MQTT_PASSWORD))
        {
            Serial.println("[MQTT] : Reconnected to MQTT broker");
        }
        else
        {
            Serial.print("[MQTT] : Failed to reconnect to MQTT broker, rc=");
            Serial.print(mqttClient.state());
            Serial.println();
        }
    }
    else
    {
        Serial.println("[MQTT] : Error no WiFi Connection");
    }
}

void MqttClass::loop()
{
    if ((millis() - lastTimerReconnect) > MQTT_TIMEOUT_RECONNECT)
    {
        if (!mqttClient.connected())
        {
            Serial.println(F("[MQTT] : Not connected"));
            setup();
        }
        else
        {
            Serial.println(F("[MQTT] : Connected"));
        }
        lastTimerReconnect = millis();
    }
    if ((millis() - lastTimerPublish) > MQTT_TIMEOUT_PUBLISH && mqttClient.connected())
    {
        String topic = HOSTNAME;
        topic += "/z1";
        mqttClient.publish(topic.c_str(), String(lastTimerPublish).c_str());
        lastTimerPublish = millis();
    }
}