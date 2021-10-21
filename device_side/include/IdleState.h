#pragma once

#include "ScreenStateMachine.h"


class IdleState : public IScreenState {
public:
    IdleState(ScreenStateMachine* stateMachine);

    void handle(Input::Action action) override;
    void update(double dt) override;
    void draw(DisplayPtr display) override;

private:
    ScreenStateMachine* mStateMachine;

};