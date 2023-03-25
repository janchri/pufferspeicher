#include <WiFi.h>
#include <PubSubClient.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// Replace with your WiFi network credentials
const char *ssid = "FRITZ!Box 7590 HC";
const char *password = "04887905256483615871";

// MQTT broker details
const char *mqtt_server = "192.168.178.67";
const int mqtt_port = 1883;
const char *mqtt_user = "";
const char *mqtt_password = "";

// Temperature sensor details
#define ONE_WIRE_BUS 14
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
//DeviceAddress tempSensor0  = {0x28, 0xFF, 0x97, 0x4B, 0xA2, 0x15, 0x03, 0x92}; Kleines Board
DeviceAddress tempSensor1  = {0x28, 0x6B, 0xA9, 0x8C, 0x60, 0x22, 0x06, 0x06};
DeviceAddress tempSensor2  = {0x28, 0xD9, 0xF3, 0x69, 0x60, 0x22, 0x06, 0x8F};
DeviceAddress tempSensor3  = {0x28, 0xE8, 0xA6, 0x68, 0x60, 0x22, 0x06, 0x9D};
DeviceAddress tempSensor4  = {0x28, 0x61, 0x51, 0x6D, 0x60, 0x22, 0x06, 0x97};
DeviceAddress tempSensor5  = {0x28, 0x69, 0xD1, 0x6A, 0x60, 0x22, 0x06, 0x7B};
DeviceAddress tempSensor6  = {0x28, 0x8F, 0xCA, 0x0F, 0x60, 0x22, 0x06, 0xFD};
DeviceAddress tempSensor7  = {0x28, 0x1D, 0x64, 0x9A, 0x60, 0x22, 0x06, 0xD3};
DeviceAddress tempSensor8  = {0x28, 0xF7, 0x13, 0x43, 0x60, 0x22, 0x06, 0x9B};
DeviceAddress tempSensor9  = {0x28, 0x42, 0x60, 0x5C, 0x60, 0x22, 0x06, 0xF6};
DeviceAddress tempSensor10 = {0x28, 0x9C, 0xDB, 0x22, 0x60, 0x22, 0x06, 0xA3};

// WiFi and MQTT client instances
WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

// Function declarations
void findSensors();
void connectWiFi();
void connectMQTT();
void reconnectWiFi();
void reconnectMQTT();
void readAndPublishTemperature();

void setup()
{
  Serial.begin(115200);
  delay(1000);

  connectWiFi();
  connectMQTT();

  sensors.begin();
}

void loop()
{
  findSensors();
  reconnectWiFi();
  reconnectMQTT();

  readAndPublishTemperature();

  delay(5000);
}

void findSensors()
{
  byte i;
  byte addr[8];
  
  if (!oneWire.search(addr)) {
    Serial.println(" No more addresses.");
    Serial.println();
    oneWire.reset_search();
    delay(250);
    return;
  }
  Serial.print(" ROM =");
  for (i = 0; i < 8; i++) {
    Serial.write(' ');
    Serial.print(addr[i], HEX);
  }
}
void connectWiFi()
{
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("Connecting to WiFi...");
    delay(1000);
  }
  Serial.println("Connected to WiFi");
}

void connectMQTT()
{
  mqttClient.setServer(mqtt_server, mqtt_port);
  while (!mqttClient.connected())
  {
    Serial.println("Connecting to MQTT broker...");
    if (mqttClient.connect("ArduinoClient", mqtt_user, mqtt_password))
    {
      Serial.println("Connected to MQTT broker");
    }
    else
    {
      Serial.print("Failed to connect to MQTT broker, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" retrying in 5 seconds");
      delay(5000);
    }
  }
}

void reconnectWiFi()
{
  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("Connection lost, reconnecting to WiFi...");
    connectWiFi();
  }
}

void reconnectMQTT()
{
  if (!mqttClient.connected())
  {
    Serial.println("Connection lost, reconnecting to MQTT broker...");
    while (!mqttClient.connected())
    {
      if (mqttClient.connect("ArduinoClient", mqtt_user, mqtt_password))
      {
        Serial.println("Reconnected to MQTT broker");
      }
      else
      {
        Serial.print("Failed to reconnect to MQTT broker, rc=");
        Serial.print(mqttClient.state());
        Serial.println(" retrying in 5 seconds");
        delay(5000);
      }
    }
  }
}

void readAndPublishTemperature()
{
  sensors.requestTemperatures();
  mqttClient.publish("puffer/t1", String(sensors.getTempC(tempSensor1)).c_str());
  mqttClient.publish("puffer/t2", String(sensors.getTempC(tempSensor2)).c_str());
  mqttClient.publish("puffer/t3", String(sensors.getTempC(tempSensor3)).c_str());
  mqttClient.publish("puffer/t4", String(sensors.getTempC(tempSensor4)).c_str());
  mqttClient.publish("puffer/t5", String(sensors.getTempC(tempSensor5)).c_str());
  mqttClient.publish("puffer/t6", String(sensors.getTempC(tempSensor6)).c_str());
  mqttClient.publish("puffer/t7", String(sensors.getTempC(tempSensor7)).c_str());
  mqttClient.publish("puffer/t8", String(sensors.getTempC(tempSensor8)).c_str());
  mqttClient.publish("puffer/t9", String(sensors.getTempC(tempSensor9)).c_str());
  mqttClient.publish("puffer/t10",String(sensors.getTempC(tempSensor10)).c_str());
}