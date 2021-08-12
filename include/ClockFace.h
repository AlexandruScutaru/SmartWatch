#pragma once

#include "IDisplay.h"
#include "Timer.h"
#include <cstdint>


class ClockFace {
public:

    //making it singleton just for developing until I settle on a proper states design etc
    static ClockFace& GetInstance();

    void draw(IDisplayPtr display);
    void update(double dt);

private:
    ClockFace();
    //should be also taken care of the rest them 5

    void onSecondPassed();

    //TODO: keep time as seconds since epoch time
    //      each minute passed update these values accordingly
    //      eventually disable one second timer, as this is used for getting the visuals only
    uint8_t mSec = 0U;
    uint8_t mMin = 59U;
    uint8_t mHour = 23U;
    uint8_t mDay = 31U;
    uint8_t mMonth = 12U;
    uint16_t mYear = 2020U;

    bool mShowColon = true;
    Timer mOneSecondTimer;

};

#define CLOCK_FACE ClockFace::GetInstance()
