#pragma once

#include "Arduino.h"

//#define DEBUG_LOG

#ifdef DEBUG_LOG
    #define LOG(...)     do { Serial.print("<m>"); Serial.print(__VA_ARGS__); Serial.print("</m>");   } while(0)
    #define LOG_LN(...)  do { Serial.print("<m>"); Serial.print(__VA_ARGS__); Serial.println("</m>"); } while(0)
    #define LOG_FMT(...) do { Serial.print("<m>"); Serial.printf(__VA_ARGS__); Serial.print("</m>");  } while(0)
#else
    #define LOG(...)
    #define LOG_LN(...)
    #define LOG_FMT(...)
#endif
