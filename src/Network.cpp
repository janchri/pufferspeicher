
#include "Network.h"
#include "defaults.h"
#include "Configuration.h"

NetworkClass Network;

NetworkClass::NetworkClass()
    : apIp(192, 168, 4, 1), apNetmask(255, 255, 255, 0)
{
    dnsServer.reset(new DNSServer());
}

void NetworkClass::init()
{
    using std::placeholders::_1;

    WiFi.onEvent(std::bind(&NetworkClass::NetworkEvent, this, _1));
    setup();
}

void NetworkClass::setup()
{
    if (apEnabled)
    {
        WiFi.mode(WIFI_AP_STA);
        WiFi.softAPConfig(apIp, apIp, apNetmask);
        WiFi.softAP(AP_SSID, AP_PASSWORD);
        dnsServer->setErrorReplyCode(DNSReplyCode::NoError);
        dnsServer->start(DNS_PORT, "*", WiFi.softAPIP());
        dnsServerStatus = true;
    }
    else
    {
        dnsServer->stop();
        dnsServerStatus = false;
        WiFi.hostname(HOSTNAME);
        WiFi.setScanMethod(WIFI_ALL_CHANNEL_SCAN);
        WiFi.setSortMethod(WIFI_CONNECT_AP_BY_SIGNAL);
        WiFi.mode(WIFI_STA);
        WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    }
}

void NetworkClass::loop()
{
    if ((millis() - lastTimerCall) > WIFI_TIMEOUT_RECONNECT)
    {
        if (WiFi.localIP()[0] != 0)
        {
            Serial.println(F("[WiFi] :  Connected"));
        }
        else
        {
            Serial.println(F("[WiFi] : Not Connected"));
        }
        lastTimerCall = millis();
    }
}

void NetworkClass::NetworkEvent(WiFiEvent_t event)
{
    switch (event)
    {
    case ARDUINO_EVENT_WIFI_STA_CONNECTED:
        Serial.println(F("[WiFi] : WiFi connected"));
        break;
    case ARDUINO_EVENT_WIFI_STA_DISCONNECTED:
        Serial.println(F("[WiFi] : WiFi disconnected"));
        WiFi.reconnect();
        break;
    case ARDUINO_EVENT_WIFI_STA_GOT_IP:
        Serial.printf("[WiFi] : WiFi got ip: %s\r\n", WiFi.localIP().toString().c_str());
        Serial.println();
        break;
    default:
        break;
    }
}

bool NetworkClass::isConnected(){
    return WiFi.localIP()[0] != 0;
}
