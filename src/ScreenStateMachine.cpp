#include "ScreenStateMachine.h"
#include "Display.h"


ScreenStateMachine::ScreenStateMachine(Display& display)
    : mCurrentState(nullptr)
    , mDisplay(display)
 {}

ScreenStateMachine::~ScreenStateMachine() {}


void ScreenStateMachine::setState(std::shared_ptr<IScreenState> state) {
    mDisplay.clearAndShow();
    mCurrentState = state;
}

std::shared_ptr<IScreenState> ScreenStateMachine::getCurrentState() {
    return mCurrentState;
}

void ScreenStateMachine::handle(Input::Action action) {
    if (mCurrentState) {
        mCurrentState->handle(action);
    }
}

void ScreenStateMachine::update(double dt) {
    if (mCurrentState) {
        mCurrentState->update(dt);
    }
}

void ScreenStateMachine::draw() {
    if (mCurrentState) {
        mCurrentState->draw(mDisplay);
    }
}

void ScreenStateMachine::changeState(std::shared_ptr<IScreenState> state) {
    mDisplay.clearAndShow();
    if(mCurrentState != state) {
        mCurrentState = state;
    }
}
