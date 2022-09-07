#include "ClockFace.h"

#include "Display/IDisplay.h"
#include "Ui/DrawStrategies/IClockFaceDrawStrategy.h"
#include "Misc/TimeData.h"


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
