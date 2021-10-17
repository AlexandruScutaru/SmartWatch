#include "ListWidget.h"

#include "Display.h"
#include "IListWidgetDrawStrategy.h"


ListWidget::ListWidget(const vec2& pos, const vec2& size, const IListWidgetDrawStrategyPtr& drawStragety)
    : mDrawStrategy(drawStragety)
    , mPos(pos)
    , mSize(size)
{}

void ListWidget::update(double dt) {}

void ListWidget::draw(DisplayPtr display) {
    drawAt(display, mPos);
}

void ListWidget::drawAt(DisplayPtr display, const vec2& pos) {
    if (mWidgetsList.size() && mDrawStrategy) {
        mDrawStrategy->drawList(display, pos, mSize, mWidgetsList, mCurrentlySelected);
    }
}

void ListWidget::addItem(WidgetPtr item) {
    mWidgetsList.push_back(item);
}

void ListWidget::setFocusedItem(size_t idx, bool focus) {
    if (mWidgetsList.isInsideBounds(idx) && mWidgetsList[idx]) {
        mWidgetsList[idx]->setFocused(focus);
    }
}

void ListWidget::onSingleTap() {
    setFocusedItem(mCurrentlySelected, false);
    mCurrentlySelected++;
    if (mCurrentlySelected == mWidgetsList.size()) {
        mCurrentlySelected = 0;
    }
    setFocusedItem(mCurrentlySelected, true);
}

void ListWidget::onDoubleTap() {
    if (mWidgetsList.isInsideBounds(mCurrentlySelected) && mWidgetsList[mCurrentlySelected]) {
        mWidgetsList[mCurrentlySelected]->trigger();
    }
}
