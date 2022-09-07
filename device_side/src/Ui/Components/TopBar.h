#pragma once

#include "BatteryIndicator.h"

#include <memory>

class IDisplay;
using DisplayPtr = std::shared_ptr<IDisplay>;


class TopBar {
public:
    void draw(DisplayPtr display);
    void update(double dt);

private:
    BatteryIndicator mBatteryIndicator;

};
