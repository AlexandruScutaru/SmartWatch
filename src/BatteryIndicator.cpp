#include "BatteryIndicator.h"
#include "Display.h"

#include <Arduino.h>

#define PIN_BATTERY_LEVEL           33
#define PERCENTAGE_BIAS             0.2
#define MAX_ANALOG_READ             4096.0
#define REFERENCE_VOLTAGE           3.3


//lipo charge levels
const BatteryIndicator::VoltagePercentagePair BatteryIndicator::mVoltageRanges[] = {
    { 4.20, 100 }, //avoid full charge
    { 4.15,  95 }, //charge at most to this point
    { 4.11,  90 },
    { 4.08,  85 },
    { 4.02,  80 },
    { 3.98,  75 },
    { 3.95,  70 },
    { 3.91,  65 },
    { 3.87,  60 },
    { 3.85,  55 },
    { 3.84,  50 },
    { 3.82,  45 },
    { 3.80,  40 },
    { 3.79,  35 },
    { 3.77,  30 },
    { 3.75,  25 },
    { 3.73,  20 }, //recharge now
    { 3.71,  15 }, //bad
    { 3.69,  10 }, //very bad
    { 3.61,   5 }, //critical
    { 3.27,   0 }, //dead
};

const size_t BatteryIndicator::mNumberRanges = sizeof(BatteryIndicator::mVoltageRanges) / sizeof(BatteryIndicator::mVoltageRanges[0]);


BatteryIndicator::BatteryIndicator() {
    auto reading = readBatteryVoltage();
    mVoltage = reading.voltage;
    mPercentage = reading.percentage;

    mBatteryReadTimer.start(5000, false, [this]() {
        auto reading = readBatteryVoltage();
        //not sure if this will do much, but eh at least it is a smaller increment, so battery level doesn't seem too jumpy
        mVoltage = (mVoltage + reading.voltage) / 2.0;
        mPercentage = (mPercentage + reading.percentage) / 2.0;
    });
}

void BatteryIndicator::update(double dt) {
    mBatteryReadTimer.update();
}

void BatteryIndicator::draw(Display& display) {
    //TODO: limit the usage of magic numbers like these
    display().drawRect(mPosX, mPosY+5, mWidth, mHeight, SSD1306_WHITE);
    display().fillRect(mPosX+1, mPosY+5, (mWidth-2) * (mPercentage / 100.0), mHeight, SSD1306_WHITE);
    display().fillRect(mPosX+mWidth, mPosY+7, 2, 4, SSD1306_WHITE);
    display().setCursor(mPosX + mWidth+6, mPosY + 2);
    display().print(mPercentage);
}

uint8_t BatteryIndicator::getPercetnage() {
    return mPercentage;
}

double BatteryIndicator::getVoltage() {
    return mVoltage;
}

BatteryIndicator::VoltagePercentagePair BatteryIndicator::readBatteryVoltage() {
    VoltagePercentagePair reading;
    //2* is used because max voltage of battery (4.2V) exceeds the analog read of 3.3v of the board
    //so the battery sensing wire is part of a voltage divider to be in the expected range [0, 3.3]
    //the PERCENTAGE_BIAS (0.2) is empirically deduced to get a closer voltage to a real meter reading
    reading.voltage = 2 * (REFERENCE_VOLTAGE * analogRead(PIN_BATTERY_LEVEL) / MAX_ANALOG_READ) + PERCENTAGE_BIAS;

    size_t index;
    for (index = 0; index < mNumberRanges; index++) {
        if (reading.voltage > mVoltageRanges[index].voltage)
            break;
    }

    if(index == mNumberRanges)
        reading.percentage = 0U;

    if(index)
        index--;

    reading.percentage = min((int)((reading.voltage - mVoltageRanges[index+1].voltage) / (mVoltageRanges[index].voltage - mVoltageRanges[index+1].voltage) *
                                   (mVoltageRanges[index].percentage - mVoltageRanges[index+1].percentage) + mVoltageRanges[index+1].percentage), 100);

    return reading;
}
