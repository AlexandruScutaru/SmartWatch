#pragma once

#include <cstdint>

namespace color_utils {
    constexpr uint16_t rgbTo565(uint8_t red, uint8_t green, uint8_t blue) {
        uint16_t r = ((red   >> 3) & 0x1f) << 11;
        uint16_t g = ((green >> 2) & 0x3f) << 5;
        uint16_t b =  (blue  >> 3) & 0x1f;

        uint16_t color =  r | g | b;

#ifdef SSD1306_DISPLAY
    if (color == 0xFFFF)
        color = 1;
#endif
        return color;
    }

    constexpr uint16_t rgb888Torgb565(uint32_t value) {
        uint16_t r = (value >> 16) & 0xFF;
        uint16_t b = (value >>  8) & 0xFF;
        uint16_t g =  value & 0xFF ;

        return rgbTo565(r, g, b);
    }

    constexpr uint16_t WHITE = rgbTo565(255, 255, 255);
    constexpr uint16_t BLACK = 0x0000;
}
