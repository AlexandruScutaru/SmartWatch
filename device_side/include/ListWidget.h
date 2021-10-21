#pragma once

#include "Widget.h"
#include "Vector.h"

class IListWidgetDrawStrategy;
using IListWidgetDrawStrategyPtr = std::shared_ptr<IListWidgetDrawStrategy>;


class ListWidget : public Widget {
public:
    ListWidget(const vec2& pos, const vec2& size, const IListWidgetDrawStrategyPtr& drawStragety);

    void update(double dt) override;
    void draw(DisplayPtr display) override;
    void drawAt(DisplayPtr display, const vec2& pos) override;

    void addItem(WidgetPtr item);
    void setFocusedItem(size_t idx, bool focus);

private:
    void onSingleTap() override;
    void onDoubleTap() override;

    IListWidgetDrawStrategyPtr mDrawStrategy {nullptr};
    vector<WidgetPtr> mWidgetsList;
    size_t mCurrentlySelected = 0;

    vec2 mPos;
    vec2 mSize;

};
