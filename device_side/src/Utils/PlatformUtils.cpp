#include "PlatformUtils.h"

#include <Arduino.h>


unsigned int platform_utils::getElapsedTime() {
    return millis();
}

double platform_utils::analogRead(uint8_t pin) {
    return analogRead(pin);
}
