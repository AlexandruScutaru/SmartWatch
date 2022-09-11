#pragma once

#include "Timer.h"

#include <cstdint>


namespace clock_time {
    struct TimeData {
        int8_t sec = 10;
        int8_t min = 23;
        int8_t hour = 20;
        int8_t day = 16;
        int8_t month = 10;
        int16_t year = 2021;
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
