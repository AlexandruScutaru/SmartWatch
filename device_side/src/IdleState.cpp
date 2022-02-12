#include "IdleState.h"
#include "InputButton.h"
#include "MainScreenState.h"


IdleState::IdleState(ScreenStateMachine* stateMachine) 
    : IScreenState()
{
    mStateMachine = stateMachine;
}

void IdleState::handle(input::Action action) {
    switch (action)
    {
    case input::Action::SINGLE_PRESS:
        mStateMachine->changeState(std::shared_ptr<IScreenState>(new MainScreenState(mStateMachine)));
        break;
    default:
        break;
    }
}

void IdleState::update(double dt) {}

void IdleState::draw(DisplayPtr display) {}
