#pragma once

#include "Widget.h"

#include <functional>

using OnClickFunction = std::function<void()>;


class Button : public Widget {
public:
    Button(const char* text, const vec2& pos, const vec2& size, OnClickFunction func = nullptr);
    virtual ~Button();

    void setFocused(bool focus) override;
    vec2 getPosition() override;
    vec2 getSize() override;
    void trigger() override;

    void update(double dt) override;
    void draw(DisplayPtr display) override;
    virtual void drawAt(DisplayPtr display, const vec2& pos) = 0;

protected:
    const vec2 mPos;
    const vec2 mSize;
    const char* mText{ nullptr };
    bool mFocused = false;

    OnClickFunction mFunc{ nullptr };

};
