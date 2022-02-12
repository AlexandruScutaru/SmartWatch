#include "ScreenStateMachine.h"

#include "Ble.h"


ScreenStateMachine::ScreenStateMachine() {}

ScreenStateMachine::~ScreenStateMachine() {}


void ScreenStateMachine::init(DisplayPtr display) {
    mDisplay = display;
}

void ScreenStateMachine::setState(std::shared_ptr<IScreenState> state) {
    if (mDisplay) {
        mDisplay->clearAndDisplay();
    }
    mCurrentState = state;
}

std::shared_ptr<IScreenState> ScreenStateMachine::getCurrentState() {
    return mCurrentState;
}

void ScreenStateMachine::handle(input::Action action) {
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
    if (mDisplay) {
        mDisplay->clearAndDisplay();
    }
    if(mCurrentState != state) {
        mCurrentState = state;
    }
}

void ScreenStateMachine::setBle(BLEPtr ble) {
    mBle = ble;
}

void ScreenStateMachine::sendData(const std::string& data) {
    if (mBle) {
        mBle->sendData(data);
    }
}