#include "SettingsState.h"
#include "MainScreenState.h"
#include "IdleState.h"
#include "ListWidget.h"
#include "VListWidgetDrawStrategy.h"
#include "Logger.h"
#include "TextButton.h"
#include "Checkbox.h"
#include "InputButton.h"

#define LIST_ITEM_WIDTH 124
#define LIST_ITEM_HEIGHT 12

#define NAME "Settings"


SettingsState::SettingsState(ScreenStateMachine* stateMachine) 
    : IScreenState()
{
    mStateMachine = stateMachine;
    mTimer.start(5000, true, [stateMachine]() {
        if (stateMachine) {
            stateMachine->changeState(std::shared_ptr<IScreenState>(new IdleState(stateMachine)));
        }
    });

    mListWidget = std::make_shared<ListWidget>(vec2(0, 16), vec2(128, 48), IListWidgetDrawStrategyPtr(new VListWidgetDrawStrategy()));
    setupMenu();
}

void SettingsState::handle(input::Action action) {
    if (action == input::Action::LONG_PRESS) {
        mStateMachine->changeState(std::shared_ptr<IScreenState>(new MainScreenState(mStateMachine)));
        return;
    }

    if (action != input::Action::NONE) {
        mTimer.reset();
    }
    mListWidget->handle(action);
}

void SettingsState::update(double dt) {
    mTimer.update();
}

void SettingsState::draw(DisplayPtr display) {
    if (!display) {
        return;
    }

    display->clear();

    display->setTextSize(1);
    display->setTextColor(SSD1306_WHITE);
    display->setCursor((128 - strlen(NAME) * 6) / 2, 4);
    display->print(NAME);

    mListWidget->draw(display);

    display->display();
}

void SettingsState::setupMenu() {
    mListWidget->addItem(std::make_shared<TextButton>("Rand battery" , vec2(LIST_ITEM_WIDTH, LIST_ITEM_HEIGHT), [this]() {
        mStateMachine->sendData(String(random(0, 101)).c_str());
    }));
    mListWidget->addItem(std::make_shared<TextButton>("MyButton1" , vec2(LIST_ITEM_WIDTH, LIST_ITEM_HEIGHT)));
    mListWidget->addItem(std::make_shared<Checkbox>("MyCheckbox1", vec2(LIST_ITEM_WIDTH, LIST_ITEM_HEIGHT)));
    mListWidget->addItem(std::make_shared<Checkbox>("MyCheckbox2", vec2(LIST_ITEM_WIDTH, LIST_ITEM_HEIGHT)));
    mListWidget->addItem(std::make_shared<TextButton>("MyButton2" , vec2(LIST_ITEM_WIDTH, LIST_ITEM_HEIGHT), []() {}));
    mListWidget->addItem(std::make_shared<TextButton>("MyButton3" , vec2(LIST_ITEM_WIDTH, LIST_ITEM_HEIGHT)));

    mListWidget->setFocusedItem(0, true);
}
