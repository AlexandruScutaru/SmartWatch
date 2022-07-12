#include "SettingsView.h"
#include "ListWidget.h"
#include "VListWidgetDrawStrategy.h"
#include "Logger.h"
#include "TextButton.h"
#include "Checkbox.h"
#include "StackView.h"
#include "Display.h"

#define LIST_ITEM_WIDTH 124
#define LIST_ITEM_HEIGHT 12

#define NAME "Settings"


SettingsView::SettingsView(StackView& stackView)
    : mStackView(stackView)
{
    LOG_LN("SettingsView::ctor");
    mListWidget = std::make_shared<ListWidget>(vec2(0, 16), vec2(128, 48), IListWidgetDrawStrategyPtr(new VListWidgetDrawStrategy()));
    setupMenu();
}

SettingsView::~SettingsView() {
    LOG_LN("SettingsView::dtor");
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
    display->setTextColor(SSD1306_WHITE);
    display->setCursor((128 - strlen(NAME) * 6) / 2, 4);
    display->print(NAME);

    mListWidget->draw(display);

    display->display();
}

void SettingsView::setupMenu() {
    mListWidget->addItem(std::make_shared<TextButton>("Rand battery" , vec2(LIST_ITEM_WIDTH, LIST_ITEM_HEIGHT), [this]() {
        // find a (better) way to do this
    }));
    mListWidget->addItem(std::make_shared<TextButton>("MyButton1" , vec2(LIST_ITEM_WIDTH, LIST_ITEM_HEIGHT)));
    mListWidget->addItem(std::make_shared<Checkbox>("MyCheckbox1", vec2(LIST_ITEM_WIDTH, LIST_ITEM_HEIGHT)));
    mListWidget->addItem(std::make_shared<Checkbox>("MyCheckbox2", vec2(LIST_ITEM_WIDTH, LIST_ITEM_HEIGHT)));
    mListWidget->addItem(std::make_shared<TextButton>("MyButton2" , vec2(LIST_ITEM_WIDTH, LIST_ITEM_HEIGHT), []() {}));
    mListWidget->addItem(std::make_shared<TextButton>("MyButton3" , vec2(LIST_ITEM_WIDTH, LIST_ITEM_HEIGHT)));

    mListWidget->setFocusedItem(0, true);
}
