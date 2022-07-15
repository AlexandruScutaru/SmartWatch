#pragma once

#include <memory>

class vec2;

template<class T>
class vector;

class Display;
using DisplayPtr = std::shared_ptr<Display>;

class Widget;
using WidgetPtr = std::shared_ptr<Widget>;


class IListWidgetDrawStrategy {
public:
    virtual ~IListWidgetDrawStrategy() {}

    virtual void drawList(DisplayPtr display, const vec2& pos, const vec2& size, const vector<WidgetPtr>& list, size_t currentItemIdx) = 0;

};

using IListWidgetDrawStrategyPtr = std::shared_ptr<IListWidgetDrawStrategy>;
