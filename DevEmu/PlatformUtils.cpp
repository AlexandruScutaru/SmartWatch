#include "Utils/PlatformUtils.h"
#include "mainwindow.h"

#include <chrono>

static constexpr uint8_t PIN_BATTERY_LEVEL = 33;


unsigned int platform_utils::getElapsedTime() {
    static auto gStart = std::chrono::steady_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - gStart).count();
}

double platform_utils::analogRead(uint8_t pin) {
    switch (pin) {
        case PIN_BATTERY_LEVEL: return MAIN_WINDOW.getBatteryVoltage() * 4096 / 3.3;
        default: return 0;
    }
}
