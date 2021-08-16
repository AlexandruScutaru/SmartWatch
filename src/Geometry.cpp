#include "Geometry.h"

Geometry::Geometry() {}


Geometry& Geometry::x(int16_t x) {
    mX = x;
    return *this;
}

Geometry& Geometry::y(int16_t y) {
    mY = y;
    return *this;
}

Geometry& Geometry::w(int16_t w) {
    mW = w;
    return *this;
}

Geometry& Geometry::h(int16_t h) {
    mH = h;
    return *this;
}

Geometry& Geometry::text(const char* text) {
    mText = text;
    return *this;
}

Geometry& Geometry::iconBuffer(const uint8_t* icon) {
    mIconBuffer = icon;
    return *this;
}

Geometry& Geometry::focused(bool focused) {
    mFocused = focused;
    return *this;
}
