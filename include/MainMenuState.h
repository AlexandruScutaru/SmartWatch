#pragma once

#include "ScreenStateMachine.h"
#include "Timer.h"
#include "Widget.h"

class ListWidget;


class MainMenuState : public IScreenState {
public:
    MainMenuState(ScreenStateMachine* stateMachine);

    void handle(Input::Action action) override;
    void update(double dt) override;
    void draw(DisplayPtr display) override;

private:
    void setupMenu();

    ScreenStateMachine* mStateMachine;
    Timer mTimer;
    std::shared_ptr<ListWidget> mListWidget;

};
