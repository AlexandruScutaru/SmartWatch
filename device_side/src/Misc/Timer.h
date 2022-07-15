#pragma once

#include <functional>

using TimerFunction = std::function<void(void)>;

class Timer {
public:
    void start(uint32_t period, bool singleShot, TimerFunction func);
    void reset();
    void restart();

    void stop();
    void update();

private:
    bool mSingleShot = true;
    bool mStopped = true;
    uint32_t mPeriod = 0U;
    uint32_t mStartTime = 0U;

    TimerFunction mFunc = nullptr;
};
