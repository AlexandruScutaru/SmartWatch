#include "InputButton.h"

#include <Arduino.h>

#define PIN_BUTTON_INPUT      4
#define DEBOUNCE_TIMEOUT     50
#define INPUT_READ_TIMEOUT  700


namespace input {
    Button::Button() {
        pinMode(PIN_BUTTON_INPUT, INPUT_PULLUP);
    }

    void Button::setCallback(const OnUserActionFunc& func) {
        mFunc = func;
    }

    void Button::update() {
        bool buttonState = digitalRead(PIN_BUTTON_INPUT);
        uint32_t time = millis();

        if (!buttonState && !mCountingInProgress) {
            mCountingInProgress = true;
            mCountingStartTime = time;
            mLastDebounceTime = mCountingStartTime;
        }

        if (time - mLastDebounceTime > DEBOUNCE_TIMEOUT) {
            if (!buttonState && mLastButtonState) {
                mPressesCount++;
            }
            mLastButtonState = buttonState;
            mLastDebounceTime = time;
        }

        if (time - mCountingStartTime > INPUT_READ_TIMEOUT) {
            switch (mPressesCount) {
            case 1:
                if (mLastButtonState) {
                    if (mFunc) mFunc(Action::SINGLE_PRESS);
                } else {
                    if (mFunc) mFunc(Action::LONG_PRESS);
                }
                break;
            case 2:
                if (mFunc) mFunc(Action::DOUBLE_PRESS);
                break;
            case 3:
                if (mFunc) mFunc(Action::TRIPLE_PRESS);
                break;
            default: break;
            }

            mCountingStartTime = time;
            mCountingInProgress = false;
            mPressesCount = 0;
        }
    }
}  // input
