#pragma once

#include "Timer.h"

#include <cstdint>

class Display;


class BatteryIndicator {
public:
    BatteryIndicator();

    void update(double dt);
    void draw(Display& display);

    uint8_t getPercetnage();
    double getVoltage();

private:
    struct VoltagePercentagePair {
        double voltage;
        uint8_t percentage;
    };

    static const VoltagePercentagePair mVoltageRanges[];
    static const size_t mNumberRanges;

    VoltagePercentagePair readBatteryVoltage();

    uint16_t mPosX = 0U;
    uint16_t mPosY = 0U;
    uint16_t mWidth = 20U;
    uint16_t mHeight = 8U;

    uint8_t mPercentage = 0U;
    double mVoltage = 0.0;

    Timer mBatteryReadTimer;

};
