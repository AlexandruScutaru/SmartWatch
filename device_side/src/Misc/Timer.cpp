#include "Timer.h"

#include <Arduino.h>


void Timer::start(uint32_t period, bool singleShot, TimerFunction func) {
    mPeriod = period;
    mFunc = func;
    mSingleShot = singleShot;
    mStartTime = millis();
    mStopped = false;
}

void Timer::reset() {
    mStartTime = millis();
}

void Timer::stop() {
    mStopped = true;
    mStartTime = 0U;
}

void Timer::update() {
    if(mStopped) {
        return;
    }

    if (millis() - mStartTime >= mPeriod) {
        if (mFunc) {
            mFunc();
        }

        if (mSingleShot) {
            mStopped = true;
            mStartTime = 0U;
            return;
        }
        mStartTime = millis();
    }
}

void Timer::restart() {
    if (mPeriod) {
        mStartTime = millis();
        mStopped = false;
    }
}
