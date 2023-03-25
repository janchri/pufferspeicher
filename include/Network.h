#pragma once

#include <DNSServer.h>
#include <WiFi.h>
#include <vector>

class NetworkClass {
public:
    NetworkClass();
    void init();
    void loop();
    bool isConnected();

private:
    void setup();
    void NetworkEvent(WiFiEvent_t event);


    uint32_t lastTimerCall = 0;
    
    bool apEnabled = false;

    IPAddress apIp;
    IPAddress apNetmask;
    const byte DNS_PORT = 53;
    std::unique_ptr<DNSServer> dnsServer;
    bool dnsServerStatus = false;

};

extern NetworkClass Network;