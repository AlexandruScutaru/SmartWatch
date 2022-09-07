#include "BatteryIndicator.h"

#include "Display/IDisplay.h"
#include "Misc/BatteryLevelReader.h"
#include "Utils/ColorUtils.h"

void BatteryIndicator::update(double dt) {}

void BatteryIndicator::draw(DisplayPtr display) {
    if (!display)
        return;

    auto batteryLevel = BATTERY_LEVEL_READER.getBatterylevel().percentage;

    //TODO: limit the usage of magic numbers like these
    display->drawRect(mPosX, mPosY+5, mWidth, mHeight, color_utils::WHITE);
    display->fillRect(mPosX+1, mPosY+5, (mWidth-2) * (batteryLevel / 100.0), mHeight, color_utils::WHITE);
    display->fillRect(mPosX+mWidth, mPosY+7, 2, 4, color_utils::WHITE);
    display->setCursor(mPosX + mWidth+6, mPosY + 2);
    display->print(batteryLevel);
}
