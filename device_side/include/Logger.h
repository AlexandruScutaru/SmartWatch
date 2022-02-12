#pragma once

#include "Arduino.h"

#ifdef SHOULD_LOG
    #define LOG(...)     Serial.print(__VA_ARGS__)
    #define LOG_LN(...)  Serial.print(__VA_ARGS__)
    #define LOG_FMT(...) Serial.printf(__VA_ARGS__)
#else
    #define LOG(...)
    #define LOG_LN(...)
    #define LOG_FMT(...)
#endif
