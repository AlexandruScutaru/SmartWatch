#pragma once

#include <memory>
#include <cstdint>

class IDisplay;
using DisplayPtr = std::shared_ptr<IDisplay>;


class BatteryIndicator {
public:
    void update(double dt);
    void draw(DisplayPtr display);

private:
    uint16_t mPosX = 0U;
    uint16_t mPosY = 0U;
    uint16_t mWidth = 20U;
    uint16_t mHeight = 8U;

};
