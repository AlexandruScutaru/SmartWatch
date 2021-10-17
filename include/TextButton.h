#pragma once

#include "Button.h"


class TextButton : public Button {
public:
    TextButton(const char* text, const vec2& pos, const vec2& size, OnClickFunction func = nullptr);
    TextButton(const char* text, const vec2& size, OnClickFunction func = nullptr);

    void drawAt(DisplayPtr display, const vec2& pos) override;

private:

};
