#pragma once

#include "ScreenStateMachine.h"


class MainScreenState : public IScreenState {
public:
    MainScreenState(ScreenStateMachine* stateMachine);

    void handle(Input::Action action) override;
    void update(double dt) override;
    void draw(Display& display) override;

private:
    ScreenStateMachine* mStateMachine;
    long timerStart;

};
