#include "TimeData.h"

static int8_t MONTHS_ARR[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

using namespace clock_time;

Time& Time::GetInstance() {
    static Time instance;
    return instance;
}

Time::Time() {
    // I don't have a RTC on board.. will rely on getting the actual time
    // from the connected mobile device at some time interval to limit drift off
    mOneSecondTimer.start(1000, false, [this]() {
        onSecondPassed();
    });
}

void Time::update(double dt) {
    mOneSecondTimer.update();
}

const TimeData& Time::getTimeData() const {
    return mTime;
}

void Time::onSecondPassed() {
    //this was writte at 3 AM, I just wanted to see some values on screen...
    mTime.sec++;
    if (mTime.sec == 60) {
        mTime.sec = 0;
        mTime.min++;
        if (mTime.min == 60) {
            mTime.min = 0;
            mTime.hour++;
            if (mTime.hour == 24) {
                mTime.hour = 0;
                mTime.day++;
                if(mTime.day > MONTHS_ARR[mTime.month-1]) {
                    if (mTime.month != 2 || !isLeapYear()) {
                        mTime.day = 1;
                        mTime.month++;
                        if (mTime.month > 12) {
                            mTime.month = 1;
                            mTime.year++;
                        }
                    }
                }
            }
        }
    }
}

bool Time::isLeapYear() {
    if (mTime.year % 400 == 0)
        return true;

    if (mTime.year % 100 == 0)
        return false;

    if (mTime.year % 4 == 0)
        return true;

    return false;
}
