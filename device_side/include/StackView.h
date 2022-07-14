#pragma once

#include "Timer.h"

#include <memory>
#include <vector>

class IView;
using IViewPtr = std::shared_ptr<IView>;

class Display;
using DisplayPtr = std::shared_ptr<Display>;

namespace input {
    enum class Action;
}


class StackView {
public:
    void init(DisplayPtr display);

    void push(IViewPtr view);
    IViewPtr pop();
    void popLater();
    IViewPtr peek();

    void handle(input::Action action);
    void update(double dt);
    void draw();

private:
    void clear();

    bool mPopLater{ false };
    DisplayPtr mDisplay;
    Timer mTimer;
    std::vector<IViewPtr> mStack;
};
