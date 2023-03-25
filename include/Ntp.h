#pragma once

class NtpClass {
public:
    NtpClass();
    void init();

    void setServer();
    void setTimezone();
};

extern NtpClass Ntp;