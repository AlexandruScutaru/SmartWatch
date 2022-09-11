#pragma once

#include <cstdint>


namespace platform_utils {
    unsigned int getElapsedTime();
    double analogRead(uint8_t pin);
}
