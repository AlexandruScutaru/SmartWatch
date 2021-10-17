#pragma once

#include "Button.h"

enum class Icon;


class IconButton : public Button {
public:
    IconButton(Icon icon, const char* text, const vec2& pos, const vec2& size, OnClickFunction func = nullptr);

    void drawAt(DisplayPtr display, const vec2& pos) override;

private:
    Icon mIcon;

};
