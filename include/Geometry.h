#pragma once

#include <cstdint>


class Geometry {
public:
    Geometry();

    Geometry& x(int16_t x);
    Geometry& y(int16_t y);
    Geometry& w(int16_t w);
    Geometry& h(int16_t h);
    Geometry& text(const char* text);
    Geometry& iconBuffer(const uint8_t* icon);
    Geometry& focused(bool focused);

private:
    int16_t mX = 0;
    int16_t mY = 0;
    int16_t mW = 1;
    int16_t mH = 1;

    const char* mText = nullptr;
    const uint8_t* mIconBuffer = nullptr;

    bool mFocused = false;

};
