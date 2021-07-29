#include "MainScreenState.h"
#include "IdleState.h"
#include "Display.h"
#include "BatteryUtils.h"


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
    mTimer.update();
}

void MainScreenState::draw(Display& display) {
    display().clearDisplay();
    display().setCursor(0, 0);
    display().print(BatteryUtils::GetBatteryVoltage(), 2);
    display().print("~");
    display().print(BatteryUtils::GetBatteryLevel());
    display().setCursor(0, 10);
    display().print("main screen");
    display().display();
}
