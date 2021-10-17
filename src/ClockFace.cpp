#include "ClockFace.h"

#define PRINT_WITH_LEADING_ZERO(value)        if ((value) < 10U) display->print("0"); display->print((value))


static uint8_t MONTHS_ARR[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

ClockFace& ClockFace::GetInstance() {
    static ClockFace instance;
    return instance;
}

ClockFace::ClockFace() {
    // I don't have a RTC on board.. will rely on getting the actual time 
    // from the connected mobile device at some time interval to limit drift off
    mOneSecondTimer.start(1000, false, [this]() {
        onSecondPassed();
    });
}

void ClockFace::draw(DisplayPtr display) {
    if (!display)
        return;

    display->setTextSize(4);
    display->setCursor(4, 16);
    PRINT_WITH_LEADING_ZERO(mHour);
    if (mShowColon)
        display->print(":");
    else
        display->print(" ");
    PRINT_WITH_LEADING_ZERO(mMin);

    display->setTextSize(2);
    display->setCursor(4, 48);
    PRINT_WITH_LEADING_ZERO(mDay);
    display->print("/");
    PRINT_WITH_LEADING_ZERO(mMonth);
    display->print("/");
    display->print(mYear);
}

void ClockFace::update(double dt) {
    mOneSecondTimer.update();
}

void ClockFace::onSecondPassed() {
    //this was writte at 3 AM, I just wanted to see some values on screen...
    mSec++;
    if (mSec == 60U) {
        mSec = 0U;
        mMin++;
        if (mMin == 60U) {
            mMin = 0U;
            mHour++;
            if (mHour == 24U) {
                mHour = 0U;
                mDay++;
                if(mDay > MONTHS_ARR[mMonth-1]) {
                    if (mMonth != 2 || !isLeapYear()) {
                        mDay = 1U;
                        mMonth++;
                        if (mMonth > 12) {
                            mMonth = 1U;
                            mYear++;
                        }
                    }
                }
            }
        }
    }

    mShowColon = !mShowColon;
}

bool ClockFace::isLeapYear() {
    if (mYear % 400 == 0)
        return true;
 
    if (mYear % 100 == 0)
        return false;
 
    if (mYear % 4 == 0)
        return true;

    return false;
}
