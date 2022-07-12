#include "StackView.h"
#include "InputButton.h"
#include "IView.h"
#include "Logger.h"
#include "MainScreenView.h"
#include "Display.h"

static int SCREEN_TIMEOUT = 5000;


void StackView::init(DisplayPtr display) {
    mDisplay = display;
    push(IViewPtr(new MainScreenView(*this)));

    mTimer.start(SCREEN_TIMEOUT, true, [this]() {
        LOG_LN("Screen timeout");
        clear();
    });

    LOG_LN("StackView inited");
}

void StackView::push(IViewPtr view) {
    mStack.push_back(view);
    mTimer.restart();
}

IViewPtr StackView::pop() {
    if (mStack.empty()) {
        return IViewPtr();
    }

    auto view = mStack.back();
    mStack.pop_back();
    return view;
}

IViewPtr StackView::peek() {
    if (mStack.empty()) {
        return IViewPtr();
    }
    return mStack.back();
}

void StackView::handle(input::Action action) {
    if (action == input::Action::NONE) {
        return;
    }

    mTimer.restart();

    if (action == input::Action::DOUBLE_PRESS && mStack.empty()) {
        push(IViewPtr(new MainScreenView(*this)));
        return;
    }

    if (action == input::Action::LONG_PRESS) {
        if (mStack.size() > 1) {
            mStack.erase(mStack.begin() + 1, mStack.end());
        }
        return;
    }

    if (!mStack.empty()) {
        if (auto view = mStack.back()) {
            view->handle(action);
        }
    }
}

void StackView::update(double dt) {
    mTimer.update();

    if (mStack.empty()) {
        return;
    }

    if (auto view = mStack.back()) {
        view->update(dt);
    }
}

void StackView::draw() {
    if (mStack.empty()) {
        return;
    }

    if (auto view = mStack.back()) {
        view->draw(mDisplay);
    }
}

void StackView::clear() {
    mStack.clear();
    mDisplay->clearAndDisplay();
}
