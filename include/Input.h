#pragma once


class Input {
public:
    Input(int buttonPin);

    enum class Action {
        NONE = 0,
        SINGLE_TAP,
        DOUBLE_TAP,
        TRIPLE_TAP,
        HOLD,
        LONG_HOLD
    };

    void init();

    Action getUserAction();

private:
    // Button timing variables
    int debounce;
    int DCgap;
    int holdTime;
    int longHoldTime;

    // Button variables
    int buttonPin;
    bool buttonVal;
    bool buttonLast;
    bool DCwaiting;
    bool DConUp;
    bool singleOK;
    long downTime;
    long upTime;
    bool ignoreUp;
    bool waitForUp;
    bool holdEventPast;
    bool longHoldEventPast;

};