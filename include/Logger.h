#pragma once

#include <Arduino.h>
#include "WString.h"

class LoggerClass
{
public:
    LoggerClass();
    void begin();
    void printf(const char *format, ...);
    void print(const String &s);
    void print(const uint32_t &num);
    void println(const String &s);
    void println(const uint32_t &num);
};


extern LoggerClass Logger;