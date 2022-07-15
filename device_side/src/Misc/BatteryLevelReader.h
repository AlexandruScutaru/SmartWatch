#pragma once

#include "Timer.h"

#include <cstdint>

struct VoltagePercentagePair {
    double voltage;
    uint8_t percentage;
};

class BatteryLevelReader {
public:
    static BatteryLevelReader& GetInstance();

    void update(double dt);
    VoltagePercentagePair getBatterylevel();

private:
    BatteryLevelReader();

    VoltagePercentagePair readBatteryVoltage();

    static const VoltagePercentagePair mVoltageRanges[];
    static const size_t mNumberRanges;

    VoltagePercentagePair mCurrentLevel;
    Timer mBatteryReadTimer;

};

#define BATTERY_LEVEL_READER BatteryLevelReader::GetInstance()
