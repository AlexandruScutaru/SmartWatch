#include "IconButton.h"

#include "Display/IDisplay.h"
#include "Ui/Resources/Icons.h"
#include "Utils/ColorUtils.h"

#include <cstring>


IconButton::IconButton(icons::IconType icon, const char* text, const vec2& pos, const vec2& size, OnClickFunction func)
    : Button(text, pos, size, func)
    , mIcon(icon)
{}

void IconButton::drawAt(DisplayPtr display, const vec2& pos) {
    const uint8_t* icon = nullptr;
    int8_t factor = 1;
    if (mFocused) {
        if (mText) {
            display->setTextColor(color_utils::WHITE);
            display->setTextSize(1);
            display->setCursor((128 - strlen(mText) * 6) / 2, 4);
            display->print(mText);
        }
        icon = icons::getIcon32(mIcon);
        factor = 2;
    } else {
        icon = icons::getIcon16(mIcon);
    }

    if (icon) {
        display->fillRect(pos.x, pos.y, 20 * factor, 20 * factor, color_utils::WHITE);
        display->fillRect(pos.x + 1 * factor, pos.y + 1 * factor, 18 * factor, 18 * factor, color_utils::BLACK);
        display->drawBitmap(pos.x + 2 * factor, pos.y + 2 * factor, icon, 16 * factor, 16 * factor, color_utils::WHITE, color_utils::BLACK);
    }
}
