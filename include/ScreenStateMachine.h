#pragma once

#include "Input.h"

#include <memory>

class Display;

class IScreenState {
public:    
    virtual void handle(Input::Action action) = 0;
    virtual void update(double dt) = 0;
    virtual void draw(Display& display) = 0;
};


class ScreenStateMachine {
public:
    ScreenStateMachine();
    ~ScreenStateMachine();

    void setState(std::shared_ptr<IScreenState> state);
    std::shared_ptr<IScreenState> getCurrentState();

    void handle(Input::Action action);
    void changeState(std::shared_ptr<IScreenState> state);
private:
    std::shared_ptr<IScreenState> mCurrentState;

};
