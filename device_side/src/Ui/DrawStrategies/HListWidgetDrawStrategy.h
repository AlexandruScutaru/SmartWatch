#pragma once

#include "IListWidgetDrawStrategy.h"


class HListWidgetDrawStrategy : public IListWidgetDrawStrategy {
public:
    void drawList(DisplayPtr display, const vec2& pos, const vec2& size, const std::vector<WidgetPtr>& list, size_t currentItemIdx) override;

};
