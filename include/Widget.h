#pragma once

#include "Input.h"

#include <functional>
#include <memory>

using OnClickFunction = std::function<void(void)>;

class Display;
using DisplayPtr = std::shared_ptr<Display>;


class Widget {
public:
    Widget();
    virtual ~Widget();

    void setOnClickFunction(OnClickFunction func);
    void handle(Input::Action action);

    virtual void update(double dt) = 0;
    virtual void draw(DisplayPtr display) = 0;

    virtual void onSingleTap() {};
    virtual void onDoubleTap() {};
    virtual void onTripleTap() {};
    virtual void onLongPress() {};

protected:
    OnClickFunction mFunc = nullptr;

};
