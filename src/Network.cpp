#include "Network.h"
#include "Logger.h"

#include <Ticker.h>
#include <time.h>

#include "defaults.h"
#include "credentials.h"
#include "Configuration.h"

Ticker wifiReconnectTimer;

NetworkClass Network;

// Private prototypes
void WiFiStationConnected(WiFiEvent_t event, WiFiEventInfo_t info);
void WiFiGotIP(WiFiEvent_t event, WiFiEventInfo_t info);
void WiFiStationDisconnected(WiFiEvent_t event, WiFiEventInfo_t info);
void connectToWifi();

NetworkClass::NetworkClass()
    : apIp(192, 168, 4, 1), apNetmask(255, 255, 255, 0)
{
    configTzTime(MY_TZ, NTP_SERVER_0, NTP_SERVER_1, NTP_SERVER_2);

    dnsServer.reset(new DNSServer());
}

void NetworkClass::init()
{
    WiFi.onEvent(WiFiStationConnected, WiFiEvent_t::ARDUINO_EVENT_WIFI_STA_CONNECTED);
    WiFi.onEvent(WiFiGotIP, WiFiEvent_t::ARDUINO_EVENT_WIFI_STA_GOT_IP);
    WiFi.onEvent(WiFiStationDisconnected, WiFiEvent_t::ARDUINO_EVENT_WIFI_STA_DISCONNECTED);

    connectToWifi();
}

void NetworkClass::loop()
{
    static uint32_t lastTimerCall = 0;
    if ((millis() - lastTimerCall) > WIFI_TIMEOUT_CHECK_STATUS_MS)
    {
        if (isConnected())
        {
            Logger.println(F("[WiFi]:  Connected"));
        }
        else
        {
            Logger.println(F("[WiFi]: Not Connected"));
        }
        lastTimerCall = millis();
    }
}

bool NetworkClass::isConnected()
{
    return WiFi.localIP()[0] != 0;
}

// Private functions
void connectToWifi()
{
    // WiFi.mode(WIFI_AP_STA);
    WiFi.mode(WIFI_STA);
    // WiFi.setOutputPower(17); // 10dBm == 10mW, 14dBm = 25mW, 17dBm = 50mW, 20dBm = 100mW
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
}

void WiFiStationConnected(WiFiEvent_t event, WiFiEventInfo_t info)
{
    Logger.println("[WiFi]: Connected to AP successfully!");
}

void WiFiGotIP(WiFiEvent_t event, WiFiEventInfo_t info)
{
    Logger.println("[WiFi]: WiFi connected");
    Logger.println("[WiFi]: IP address: ");
    Logger.println(WiFi.localIP().toString());
}

void WiFiStationDisconnected(WiFiEvent_t event, WiFiEventInfo_t info)
{
    Logger.println("[WiFi]: Disconnected from WiFi access point");
    Logger.print("[WiFi]: WiFi lost connection. Reason: ");
    Logger.println(info.wifi_sta_disconnected.reason);
    Logger.println("[WiFi]: Trying to Reconnect");

    // Logger.println("Disconnected from Wi-Fi.");
    // wifiReconnectTimer.once(10, reconnectToWifi);
    connectToWifi();
}