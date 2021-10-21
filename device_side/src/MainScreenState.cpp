#include "MainScreenState.h"
#include "MainMenuState.h"
#include "IdleState.h"
#include "ClockFace.h"


MainScreenState::MainScreenState(ScreenStateMachine* stateMachine) 
    : IScreenState()
{
    mStateMachine = stateMachine;
    mTimer.start(5000, true, [stateMachine]() {
        if (stateMachine) {
            stateMachine->changeState(std::shared_ptr<IScreenState>(new IdleState(stateMachine)));
        }
    });
}


void MainScreenState::handle(Input::Action action) {
    if (action != Input::Action::NONE) {
        mTimer.reset();
    }

    switch (action)
    {
    case Input::Action::DOUBLE_TAP:
        mStateMachine->changeState(std::shared_ptr<IScreenState>(new MainMenuState(mStateMachine)));
        break;
    default:
        break;
    }
}

void MainScreenState::update(double dt) {
    mBatteryIndicator.update(dt);
    mTimer.update();
}

void MainScreenState::draw(DisplayPtr display) {
    if (!display)
        return;

    display->clear();

    mBatteryIndicator.draw(display);
    CLOCK_FACE.draw(display);

    display->display();
}
