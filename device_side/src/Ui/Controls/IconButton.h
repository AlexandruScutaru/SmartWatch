#pragma once

#include "Button.h"

namespace icons {
    enum class IconType;
}


class IconButton : public Button {
public:
    IconButton(icons::IconType icon, const char* text, const vec2& pos, const vec2& size, OnClickFunction func = nullptr);

    void drawAt(DisplayPtr display, const vec2& pos) override;

private:
    icons::IconType mIcon;

};
