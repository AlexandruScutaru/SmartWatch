#include "MainScreenState.h"
#include "IdleState.h"
#include "Display.h"

#include <Arduino.h>

#define PIN_BATTERY_LEVEL 33


    //lipo charge levels
    //4.20 -> 100%  //avoid full charge
    //4.15 ->  95%  //charge at most to this point
    //4.11 ->  90%
    //4.08 ->  85%
    //4.02 ->  80%
    //3.98 ->  75%
    //3.95 ->  70%
    //3.91 ->  65%
    //3.87 ->  60%
    //3.85 ->  55%
    //3.84 ->  50%
    //3.82 ->  45%
    //3.80 ->  40%
    //3.79 ->  35%
    //3.77 ->  30%
    //3.75 ->  25%
    //3.73 ->  20%  //recharge now
    //3.71 ->  15%  //bad
    //3.69 ->  10%  //very bad
    //3.61 ->   5%  //critical
    //3.27 ->   0%  //dead
typedef struct {
    double voltage;
    byte percentage;
} association_t;

static association_t voltageRannges[] = {
    { 4.20, 100 },
    { 4.15,  95 },
    { 4.11,  90 },
    { 4.08,  85 },
    { 4.02,  80 },
    { 3.98,  75 },
    { 3.95,  70 },
    { 3.91,  65 },
    { 3.87,  60 },
    { 3.85,  55 },
    { 3.84,  50 },
    { 3.82,  45 },
    { 3.80,  40 },
    { 3.79,  35 },
    { 3.77,  30 },
    { 3.75,  25 },
    { 3.73,  20 },
    { 3.71,  15 },
    { 3.69,  10 },
    { 3.61,   5 },
    { 3.27,   0 },
};

static double avg;

static byte getAssociatedPercentage() {
    size_t nb = sizeof(voltageRannges) / sizeof(voltageRannges[0]);
    size_t index = 0;
    for (index = 0; index < nb; index++) {
        if (avg > voltageRannges[index].voltage)
            break;
    }

    if(index == nb)
        return 0;

    if(index)
        index--;

    return min((int)((avg - voltageRannges[index+1].voltage) / (voltageRannges[index].voltage - voltageRannges[index+1].voltage) * 
                    (voltageRannges[index].percentage - voltageRannges[index+1].percentage) + voltageRannges[index+1].percentage), 100);
}

static byte getBatteryLevel() {
    static double voltages[100] = {0};
    static size_t index = 0;

    voltages[index++] = 2 * (3.3 * analogRead(PIN_BATTERY_LEVEL) / 4095.0) + 0.2;
    static byte percentage = min((int)((voltages[0] - 3.7) / (4.2 - 3.7) * (100 - 10) + 10), 100);

    if(100 == index) {
        double sum = 0.0;
        for(size_t i = 0; i < 100; i++)
            sum += voltages[i];

        avg = sum / 100.0;
        index = 0;
        percentage = getAssociatedPercentage();
    }

    return percentage;
}


MainScreenState::MainScreenState(ScreenStateMachine* stateMachine) 
    : IScreenState()
    , timerStart(millis())
{
    mStateMachine = stateMachine;
}

void MainScreenState::handle(Input::Action action) {
    if(millis() - timerStart >= 5000) {
        mStateMachine->changeState(std::shared_ptr<IScreenState>(new IdleState(mStateMachine)));
        timerStart = millis();
    }
}

void MainScreenState::update(double dt) {

}

void MainScreenState::draw(Display& display) {
    display().clearDisplay();
    display().setCursor(0, 0);
    display().print(avg, 2);
    display().print("~");
    display().print(getBatteryLevel());
    display().setCursor(0, 10);
    display().print("main screen");
    display().display();
}
