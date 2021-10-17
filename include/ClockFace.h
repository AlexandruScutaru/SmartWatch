#pragma once

#include "Display.h"
#include "Timer.h"
#include <cstdint>


class ClockFace {
public:

    //making it singleton just for developing until I settle on a proper states design etc
    static ClockFace& GetInstance();

    void draw(DisplayPtr display);
    void update(double dt);

private:
    ClockFace();
    //should also take care of the rest of 5 rule ones

    void onSecondPassed();
    bool isLeapYear();

    //TODO: keep time as seconds since epoch time
    //      each minute passed update these values accordingly
    //      eventually disable one second timer, as this is used for getting the visuals only
    uint8_t mSec = 10U;
    uint8_t mMin = 23U;
    uint8_t mHour = 20U;
    uint8_t mDay = 16U;
    uint8_t mMonth = 10U;
    uint16_t mYear = 2021U;

    bool mShowColon = true;
    Timer mOneSecondTimer;

};

#define CLOCK_FACE ClockFace::GetInstance()
