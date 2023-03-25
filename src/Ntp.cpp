#include "Ntp.h"
#include <time.h>
#include "defaults.h"

NtpClass::NtpClass()
{
}

void NtpClass::init()
{
    setServer();
    setTimezone();
}

void NtpClass::setServer()
{
    configTime(0, 0, "pool.ntp.org");
}

void NtpClass::setTimezone()
{
    setenv("TZ", "CET-1CEST,M3.5.0,M10.5.0/3", 1);
    tzset();
}

NtpClass Ntp;