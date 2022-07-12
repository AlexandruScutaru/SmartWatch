#include "MainMenuView.h"
#include "Display.h"
#include "Logger.h"
#include "ListWidget.h"
#include "IconListWidgetDrawStrategy.h"
#include "IconButton.h"
#include "Icons.h"
#include "StackView.h"
#include "SettingsView.h"

#define LIST_ITEM_WIDTH 124
#define LIST_ITEM_HEIGHT 48


MainMenuView::MainMenuView(StackView& stackView)
    : mStackView(stackView)
{
    LOG_LN("MainMenuView::ctor");
    mListWidget = std::make_shared<ListWidget>(vec2(0, 16), vec2(128, 48), IListWidgetDrawStrategyPtr(new IconListWidgetDrawStrategy()));
    setupMenu();
}

MainMenuView::~MainMenuView() {
    LOG_LN("MainMenuView::dtor");
}

void MainMenuView::handle(input::Action action) {
    mListWidget->handle(action);
}

void MainMenuView::update(double dt) {}

void MainMenuView::draw(DisplayPtr display) {
    if (!display) {
        return;
    }

    display->clear();
    mListWidget->draw(display);
    display->display();
}

void MainMenuView::setupMenu() {
    mListWidget->addItem(std::make_shared<IconButton>(Icon::GAMES, "Games", vec2(0, 16), vec2(LIST_ITEM_WIDTH, LIST_ITEM_HEIGHT)));

    mListWidget->addItem(std::make_shared<IconButton>(Icon::SETTINGS, "Settings", vec2(0, 16), vec2(LIST_ITEM_WIDTH, LIST_ITEM_HEIGHT), [this]() {
        mStackView.push(IViewPtr(new SettingsView(mStackView)));
    }));

    mListWidget->addItem(std::make_shared<IconButton>(Icon::GAMES, "SomeOther", vec2(0, 16), vec2(LIST_ITEM_WIDTH, LIST_ITEM_HEIGHT)));

    mListWidget->setFocusedItem(0, true);
}
