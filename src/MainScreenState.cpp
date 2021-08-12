#include "MainScreenState.h"
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
}

void MainScreenState::update(double dt) {
    mBatteryIndicator.update(dt);
    //CLOCK_FACE.update(dt);
    mTimer.update();
}

void MainScreenState::draw(IDisplayPtr display) {
    if (!display)
        return;

    display->clear();

    mBatteryIndicator.draw(display);
    CLOCK_FACE.draw(display);

    display->display();
}
