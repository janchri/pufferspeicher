#pragma once

#include <DNSServer.h>
#include <WiFi.h>

class NetworkClass {
public:
    NetworkClass();
    void init();
    void loop();

    bool isConnected();
private:    
    bool apEnabled = false;

    IPAddress apIp;
    IPAddress apNetmask;
    const byte DNS_PORT = 53;
    std::unique_ptr<DNSServer> dnsServer;
    bool dnsServerStatus = false;
};

extern NetworkClass Network;