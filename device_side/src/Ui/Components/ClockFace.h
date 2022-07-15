#pragma once

#include <memory>

class Display;
using DisplayPtr = std::shared_ptr<Display>;

class IClockFaceDrawStrategy;
using IClockFaceDrawStrategyPtr = std::shared_ptr<IClockFaceDrawStrategy>;


class ClockFace {
public:
    void draw(DisplayPtr display);
    void update(double dt);

    void setClockFaceDrawStrategy(IClockFaceDrawStrategyPtr clockFaceDrawStrategy);

private:
    IClockFaceDrawStrategyPtr mDrawStrategy;

};
