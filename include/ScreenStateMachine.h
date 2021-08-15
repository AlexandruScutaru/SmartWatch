#pragma once

#include "Display.h"
#include "Input.h"

#include <memory>


class IScreenState {
public:    
    virtual void handle(Input::Action action) = 0;
    virtual void update(double dt) = 0;
    virtual void draw(DisplayPtr display) = 0;
};


class ScreenStateMachine {
public:
    ScreenStateMachine();
    ~ScreenStateMachine();

    void init(DisplayPtr display);

    void setState(std::shared_ptr<IScreenState> state);
    std::shared_ptr<IScreenState> getCurrentState();

    void handle(Input::Action action);
    void update(double dt);
    void draw();
    void changeState(std::shared_ptr<IScreenState> state);

private:
    std::shared_ptr<IScreenState> mCurrentState;
    DisplayPtr mDisplay;

};
