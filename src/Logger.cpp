#include "Logger.h"
#include "WebApi.h"
#include "defaults.h"
#include "credentials.h"

LoggerClass Logger;

LoggerClass::LoggerClass()
{
}

void LoggerClass::begin()
{
    Serial.begin(SERIAL_BAUDRATE);
    while (!Serial)
        yield();
}

void LoggerClass::printf(const char *format, ...)
{
    Serial.printf(format);

    if (WebApi._ws.count() > 0)
    {
        //WebApi._ws.printfAll(format);
    }
}

void LoggerClass::print(const String &s)
{
    Serial.print(s);
    if (WebApi._ws.count() > 0)
    {
        //WebApi._ws.textAll(s);
    }
}

void LoggerClass::print(const uint32_t &num)
{
    Serial.println(num);
    if (WebApi._ws.count() > 0)
    {
        //WebApi._ws.textAll(String(num));
    }
}

void LoggerClass::println(const String &s)
{
    Serial.println(s);
    if (WebApi._ws.count() > 0)
    {
        //WebApi._ws.textAll(s);
    }
}

void LoggerClass::println(const uint32_t &num)
{
    Serial.println(num);
    if (WebApi._ws.count() > 0)
    {
        //WebApi._ws.textAll(String(num));
    }
}