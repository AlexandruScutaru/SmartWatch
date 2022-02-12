#pragma once

#include "ScreenStateMachine.h"
#include "Timer.h"
#include "Widget.h"

class ListWidget;


class SettingsState : public IScreenState {
public:
    SettingsState(ScreenStateMachine* stateMachine);

    void handle(input::Action action) override;
    void update(double dt) override;
    void draw(DisplayPtr display) override;

private:
    void setupMenu();

    ScreenStateMachine* mStateMachine;
    Timer mTimer;
    std::shared_ptr<ListWidget> mListWidget;

};
