#pragma once

#include <memory>

class Display;
using DisplayPtr = std::shared_ptr<Display>;

namespace input {
    enum class Action;
}

class IView {
public:
    virtual void handle(input::Action) = 0;
    virtual void update(double) = 0;
    virtual void draw(DisplayPtr) = 0;
};

using IViewPtr = std::shared_ptr<IView>;
