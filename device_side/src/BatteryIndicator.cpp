#include "BatteryIndicator.h"
#include "Display.h"
#include "BatteryLevelReader.h"


void BatteryIndicator::update(double dt) {}

void BatteryIndicator::draw(DisplayPtr display) {
    if (!display)
        return;

    auto batteryLevel = BATTERY_LEVEL_READER.getBatterylevel().percentage;

    //TODO: limit the usage of magic numbers like these
    display->drawRect(mPosX, mPosY+5, mWidth, mHeight);
    display->fillRect(mPosX+1, mPosY+5, (mWidth-2) * (batteryLevel / 100.0), mHeight);
    display->fillRect(mPosX+mWidth, mPosY+7, 2, 4);
    display->setCursor(mPosX + mWidth+6, mPosY + 2);
    display->print(batteryLevel);
}
