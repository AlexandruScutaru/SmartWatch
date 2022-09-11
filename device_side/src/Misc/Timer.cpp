#include "Timer.h"

#include "Utils/PlatformUtils.h"


void Timer::start(uint32_t period, bool singleShot, TimerFunction func) {
    mPeriod = period;
    mFunc = func;
    mSingleShot = singleShot;
    mStartTime = platform_utils::getElapsedTime();
    mStopped = false;
}

void Timer::reset() {
    mStartTime = platform_utils::getElapsedTime();
}

void Timer::stop() {
    mStopped = true;
    mStartTime = 0U;
}

void Timer::update() {
    if(mStopped) {
        return;
    }

    if (platform_utils::getElapsedTime() - mStartTime >= mPeriod) {
        if (mFunc) {
            mFunc();
        }

        if (mSingleShot) {
            mStopped = true;
            mStartTime = 0U;
            return;
        }
        mStartTime = platform_utils::getElapsedTime();
    }
}

void Timer::restart() {
    if (mPeriod) {
        mStartTime = platform_utils::getElapsedTime();
        mStopped = false;
    }
}
