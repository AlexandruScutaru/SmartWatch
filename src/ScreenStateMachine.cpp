#include "ScreenStateMachine.h"


ScreenStateMachine::ScreenStateMachine()
    : mCurrentState(nullptr)
 {}


ScreenStateMachine::~ScreenStateMachine() {}

void ScreenStateMachine::setState(std::shared_ptr<IScreenState> state) {
    mCurrentState = state;
}

std::shared_ptr<IScreenState> ScreenStateMachine::getCurrentState() {
    return mCurrentState;
}

void ScreenStateMachine::handle(Input::Action action) {
    mCurrentState->handle(action);
}

void ScreenStateMachine::changeState(std::shared_ptr<IScreenState> state) {
    if(mCurrentState != state) {
        mCurrentState = state;
    }
}