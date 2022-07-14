#pragma once

#include <memory>

class Display;
using DisplayPtr = std::shared_ptr<Display>;

namespace input {
    enum class Action;
}

class StackView;

namespace views {
    template<class T>
    std::shared_ptr<T> Create(StackView& stackView) {
        auto instance = std::make_shared<T>(stackView);
        instance->init();
        return instance;
    }
}

class IView {
public:
    virtual void init() = 0;

    virtual void handle(input::Action) = 0;
    virtual void update(double) = 0;
    virtual void draw(DisplayPtr) = 0;
};

using IViewPtr = std::shared_ptr<IView>;
using IViewWeakPtr = std::weak_ptr<IView>;

