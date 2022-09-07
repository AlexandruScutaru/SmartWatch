#include "TextButton.h"

#include "Display/IDisplay.h"
#include "Utils/ColorUtils.h"


TextButton::TextButton(const char* text, const vec2& pos, const vec2& size, OnClickFunction func) 
    : Button(text, pos, size, func)
{}

TextButton::TextButton(const char* text, const vec2& size, OnClickFunction func)
    : TextButton(text, vec2(0), size, func)
{}

void TextButton::drawAt(DisplayPtr display, const vec2& pos) {
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
}
