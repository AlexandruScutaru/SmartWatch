#include "DigitalClockFaceDrawStrategy.h"

#include "Misc/TimeData.h"
#include "Display/Display.h"

#define PRINT_WITH_LEADING_ZERO(value)        if ((value) < 10U) display->print("0"); display->print((value))


void DigitalClockFaceDrawStrategy::draw(DisplayPtr display, const clock_time::TimeData& time) {
    display->setTextSize(4);
    display->setCursor(4, 16);
    PRINT_WITH_LEADING_ZERO(time.hour);
    if (time.sec & 1)
        display->print(":");
    else
        display->print(" ");
    PRINT_WITH_LEADING_ZERO(time.min);

    display->setTextSize(2);
    display->setCursor(4, 48);
    PRINT_WITH_LEADING_ZERO(time.day);
    display->print("/");
    PRINT_WITH_LEADING_ZERO(time.month);
    display->print("/");
    display->print(time.year);
}
