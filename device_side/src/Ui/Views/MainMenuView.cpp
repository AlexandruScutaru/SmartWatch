#include "MainMenuView.h"

#include "Display/IDisplay.h"
#include "Misc/Logger.h"
#include "Ui/Controls/ListWidget.h"
#include "Ui/DrawStrategies/IconListWidgetDrawStrategy.h"
#include "Ui/Controls/IconButton.h"
#include "Ui/Resources/Icons.h"
#include "StackView.h"
#include "SettingsView.h"

#define LIST_ITEM_WIDTH 124
#define LIST_ITEM_HEIGHT 48


MainMenuView::MainMenuView(StackView& stackView)
    : mStackView(stackView)
{
    LOG_LN("MainMenuView::ctor");
}

MainMenuView::~MainMenuView() {
    LOG_LN("MainMenuView::dtor");
}

void MainMenuView::init() {
    mListWidget = std::make_shared<ListWidget>(vec2(0, 16), vec2(128, 48), IListWidgetDrawStrategyPtr(new IconListWidgetDrawStrategy()));
    setupMenu();
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
    mListWidget->addItem(std::make_shared<IconButton>(icons::IconType::GAMES, "Games", vec2(0, 16), vec2(LIST_ITEM_WIDTH, LIST_ITEM_HEIGHT)));

    mListWidget->addItem(std::make_shared<IconButton>(icons::IconType::SETTINGS, "Settings", vec2(0, 16), vec2(LIST_ITEM_WIDTH, LIST_ITEM_HEIGHT), [this]() {
        mStackView.push(views::Create<SettingsView>(mStackView));
    }));

    mListWidget->addItem(std::make_shared<IconButton>(icons::IconType::UNKNOWN, "SomeOther", vec2(0, 16), vec2(LIST_ITEM_WIDTH, LIST_ITEM_HEIGHT)));

    mListWidget->setFocusedItem(0, true);
}
