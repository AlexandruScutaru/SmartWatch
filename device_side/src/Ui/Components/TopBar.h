#pragma once

#include "BatteryIndicator.h"

#include <memory>

class Display;
using DisplayPtr = std::shared_ptr<Display>;


class TopBar {
public:
    void draw(DisplayPtr display);
    void update(double dt);

private:
    BatteryIndicator mBatteryIndicator;

};
