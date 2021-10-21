#include "Button.h"

#include "Display.h"


Button::Button(const char* text, const vec2& pos, const vec2& size, OnClickFunction func) 
    : mPos(pos)
    , mSize(size)
    , mText(text)
    , mFocused(false)
    , mFunc(func)
{}

Button::~Button() {}


void Button::trigger() {
    if (mFunc) {
        mFunc();
    }
}

void Button::update(double dt) {}

void Button::draw(DisplayPtr display) {
    drawAt(display, mPos);
}

void Button::setFocused(bool focus) {
    mFocused = focus;
}

vec2 Button::getPosition() {
    return mPos;
}

vec2 Button::getSize() {
    return mSize;
}
