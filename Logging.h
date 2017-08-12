#pragma once

#include "Arduino.h"

class CLogging
{
    public:
        static const unsigned long c_initTimeoutMs = 10000;

    public:
        static void Init();
        static void log(const char* buff);
};
