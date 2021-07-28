#include "MainScreenState.h"
#include "IdleState.h"
#include "Display.h"

#include <Arduino.h>


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
    display.drawText("main screen");
}
