#pragma once

#include "defaults.h"

class ConfigurationClass
{
public:
    void init();
    bool write();
    bool read();

private:
};

extern ConfigurationClass Configuration;