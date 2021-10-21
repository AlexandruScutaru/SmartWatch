#pragma once

#include "Input.h"
#include "vec2.h"

#include <memory>

class Display;
using DisplayPtr = std::shared_ptr<Display>;


class Widget {
public:
    Widget();
    virtual ~Widget();

    void handle(Input::Action action);

    virtual void setFocused(bool focus) {};
    virtual vec2 getPosition() { return vec2(); }
    virtual vec2 getSize() { return vec2(); }
    virtual void trigger() {};

    virtual void update(double dt) = 0;
    virtual void draw(DisplayPtr display) = 0;
    virtual void drawAt(DisplayPtr display, const vec2& pos) = 0;

protected:
    virtual void onSingleTap() {};
    virtual void onDoubleTap() {};
    virtual void onTripleTap() {};
    virtual void onLongPress() {};

};

using WidgetPtr = std::shared_ptr<Widget>;
