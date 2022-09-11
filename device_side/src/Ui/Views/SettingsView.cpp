#include "SettingsView.h"

#include "Ui/Controls/ListWidget.h"
#include "Ui/DrawStrategies/VListWidgetDrawStrategy.h"
#include "Misc/Logger.h"
#include "Ui/Controls/TextButton.h"
#include "Ui/Controls/Checkbox.h"
#include "StackView.h"
#include "Display/IDisplay.h"
#include "Ui/Presenters/SettingsPresenter.h"
#include "Utils/ColorUtils.h"

#include <cstring>

#define LIST_ITEM_WIDTH 124
#define LIST_ITEM_HEIGHT 12

#define NAME "Settings"


SettingsView::SettingsView(StackView& stackView)
    : mStackView(stackView)
{
    LOG_LN("SettingsView::ctor");
}

SettingsView::~SettingsView() {
    LOG_LN("SettingsView::dtor");
}

void SettingsView::init() {
    mPresenter = std::make_shared<SettingsPresenter>(IViewWeakPtr(getPtr()));
    mListWidget = std::make_shared<ListWidget>(vec2(0, 16), vec2(128, 48), IListWidgetDrawStrategyPtr(new VListWidgetDrawStrategy()));
    setupMenu();
}

SettingsViewPtr SettingsView::getPtr() {
    return shared_from_this();
}

void SettingsView::handle(input::Action action) {
    mListWidget->handle(action);
}

void SettingsView::update(double dt) {}

void SettingsView::draw(DisplayPtr display) {
    if (!display) {
        return;
    }

    display->clear();

    display->setTextSize(1);
    display->setTextColor(color_utils::WHITE);
    display->setCursor((128 - strlen(NAME) * 6) / 2, 4);
    display->print(NAME);

    mListWidget->draw(display);

    display->display();
}

void SettingsView::setupMenu() {
    mListWidget->addItem(std::make_shared<TextButton>("MyButton" , vec2(LIST_ITEM_WIDTH, LIST_ITEM_HEIGHT), [this]() {
        mPresenter->myButtonPressed();
    }));

    mListWidget->addItem(std::make_shared<Checkbox>("MyCheckbox", vec2(LIST_ITEM_WIDTH, LIST_ITEM_HEIGHT), [this](bool state) {
        mPresenter->myCheckboxToggled(state);
    }));

    mListWidget->addItem(std::make_shared<TextButton>("Back" , vec2(LIST_ITEM_WIDTH, LIST_ITEM_HEIGHT), [this]() {
        mStackView.popLater();
    }));

    mListWidget->setFocusedItem(0, true);
}
