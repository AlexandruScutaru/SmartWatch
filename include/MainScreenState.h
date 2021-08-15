#pragma once

#include "BatteryIndicator.h"
#include "ScreenStateMachine.h"
#include "Timer.h"


class MainScreenState : public IScreenState {
public:
    MainScreenState(ScreenStateMachine* stateMachine);

    void handle(Input::Action action) override;
    void update(double dt) override;
    void draw(DisplayPtr display) override;

private:
    ScreenStateMachine* mStateMachine;
    Timer mTimer;
    BatteryIndicator mBatteryIndicator;

};
