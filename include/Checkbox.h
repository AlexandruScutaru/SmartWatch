#pragma once

#include "Widget.h"

#include <functional>

using OnStateChangedFunction = std::function<void(bool)>;


class Checkbox : public Widget {
public:
    Checkbox(const char* text, const vec2& pos, const vec2& size, OnStateChangedFunction func = nullptr);
    Checkbox(const char* text, const vec2& size, OnStateChangedFunction func = nullptr);

    void setFocused(bool focus) override;
    vec2 getPosition() override;
    vec2 getSize() override;
    void trigger() override;

    void update(double dt) override;
    void draw(DisplayPtr display) override;
    void drawAt(DisplayPtr display, const vec2& pos) override;

private:
    const vec2 mPos;
    const vec2 mSize;
    const char* mText{ nullptr};
    bool mFocused{ false };

    bool mState{ false };
    OnStateChangedFunction mFunc{ nullptr };
};
