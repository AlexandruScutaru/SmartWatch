#pragma once

#include "memory"

namespace clock_time {
    struct TimeData;
}

class IDisplay;
using DisplayPtr = std::shared_ptr<IDisplay>;

class IClockFaceDrawStrategy {
public:
    virtual void draw(DisplayPtr display, const clock_time::TimeData& time) = 0;
};

using IClockFaceDrawStrategyPtr = std::shared_ptr<IClockFaceDrawStrategy>;
