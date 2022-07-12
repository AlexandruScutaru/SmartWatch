#include "ClockFace.h"
#include "Display.h"
#include "IClockFaceDrawStrategy.h"
#include "TimeData.h"


void ClockFace::setClockFaceDrawStrategy(IClockFaceDrawStrategyPtr clockFaceDrawStrategy) {
    mDrawStrategy = clockFaceDrawStrategy;
}

void ClockFace::draw(DisplayPtr display) {
    if (!display || !mDrawStrategy) {
        return;
    }

    mDrawStrategy->draw(display, CLOCK_TIME.getTimeData());
}

void ClockFace::update(double dt) {

}
