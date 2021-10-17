#include "MainMenuState.h"
#include "MainScreenState.h"
#include "SettingsState.h"
#include "IdleState.h"
#include "ListWidget.h"
#include "IconListWidgetDrawStrategy.h"
#include "Logger.h"
#include "TextButton.h"
#include "Checkbox.h"
#include "IconButton.h"
#include "Icons.h"

#define LIST_ITEM_WIDTH 124
#define LIST_ITEM_HEIGHT 48


MainMenuState::MainMenuState(ScreenStateMachine* stateMachine) 
    : IScreenState()
{
    mStateMachine = stateMachine;
    mTimer.start(5000, true, [stateMachine]() {
        if (stateMachine) {
            stateMachine->changeState(std::shared_ptr<IScreenState>(new IdleState(stateMachine)));
        }
    });

    mListWidget = std::make_shared<ListWidget>(vec2(0, 16), vec2(128, 48), IListWidgetDrawStrategyPtr(new IconListWidgetDrawStrategy()));
    setupMenu();
}

void MainMenuState::handle(Input::Action action) {
    if (action == Input::Action::HOLD) {
        mStateMachine->changeState(std::shared_ptr<IScreenState>(new MainScreenState(mStateMachine)));
        return;
    }

    if (action != Input::Action::NONE) {
        mTimer.reset();
    }
    mListWidget->handle(action);
}

void MainMenuState::update(double dt) {
    mTimer.update();
}

void MainMenuState::draw(DisplayPtr display) {
    if (!display) {
        return;
    }

    display->clear();

    mListWidget->draw(display);

    display->display();
}

void MainMenuState::setupMenu() {
    mListWidget->addItem(std::make_shared<IconButton>(Icon::GAMES, "Games", vec2(0, 16), vec2(LIST_ITEM_WIDTH, LIST_ITEM_HEIGHT)));

    mListWidget->addItem(std::make_shared<IconButton>(Icon::SETTINGS, "Settings", vec2(0, 16), vec2(LIST_ITEM_WIDTH, LIST_ITEM_HEIGHT), [this]() {
        mStateMachine->changeState(std::shared_ptr<IScreenState>(new SettingsState(mStateMachine)));
    }));

    mListWidget->addItem(std::make_shared<IconButton>(Icon::GAMES, "SomeOther", vec2(0, 16), vec2(LIST_ITEM_WIDTH, LIST_ITEM_HEIGHT)));

    mListWidget->setFocusedItem(0, true);
}
