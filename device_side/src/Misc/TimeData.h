#pragma once

#include "Timer.h"

#include <cstdint>


namespace clock_time {
    struct TimeData {
        uint8_t sec = 10U;
        uint8_t min = 23U;
        uint8_t hour = 20U;
        uint8_t day = 16U;
        uint8_t month = 10U;
        uint16_t year = 2021U;
    };

    class Time {
    public:
        //making it singleton for now
        static Time& GetInstance();

        const TimeData& getTimeData() const;
        void update(double dt);

    private:
        Time();

        void onSecondPassed();
        bool isLeapYear();

        Timer mOneSecondTimer;
        TimeData mTime;
    };
}

#define CLOCK_TIME clock_time::Time::GetInstance()
