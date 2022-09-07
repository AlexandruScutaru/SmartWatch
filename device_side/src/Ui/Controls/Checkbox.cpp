#include "Checkbox.h"

#include "Display/IDisplay.h"
#include "Ui/Resources/Icons.h"
#include "Utils/ColorUtils.h"


Checkbox::Checkbox(const char* text, const vec2& pos, const vec2& size, OnStateChangedFunction func) 
    : mPos(pos)
    , mSize(size)
    , mText(text)
    , mFocused(false)
    , mFunc(func)
{}

Checkbox::Checkbox(const char* text, const vec2& size, OnStateChangedFunction func)
    : Checkbox(text, vec2(0), size, func)
{}

void Checkbox::trigger() {
    mState = !mState;
    if (mFunc) {
        mFunc(mState);
    }
}

void Checkbox::update(double dt) {}

void Checkbox::draw(DisplayPtr display) {
    drawAt(display, mPos);
}

void Checkbox::drawAt(DisplayPtr display, const vec2& pos) {
    uint16_t bg = color_utils::BLACK;
    uint16_t color = color_utils::WHITE;

    if (mFocused) {
        bg = color_utils::WHITE;
        color = color_utils::BLACK;
    }
    display->setTextColor(color);

    if (mText) {
        display->fillRect(pos.x, pos.y, mSize.x, mSize.y, bg);
        display->setTextSize(1);
        display->setCursor(pos.x + 2, pos.y + 2);
        display->print(mText);
    }

    display->fillRect(mSize.x - 13, pos.y, 12, 12, color);
    display->fillRect(mSize.x - 12, pos.y + 1, 10, 10, bg);
    if (mState) {
        display->drawBitmap(mSize.x - 11, pos.y + 2, icons::getIcon8(icons::IconType::CHECK_MARK), 8, 8, color, bg);
    }
}

void Checkbox::setFocused(bool focus) {
    mFocused = focus;
}

vec2 Checkbox::getPosition() {
    return mPos;
}

vec2 Checkbox::getSize() {
    return mSize;
}
