#pragma once

#include <Adafruit_SSD1306.h>

class Display {
public:
    //Reset pin # (or -1 if sharing Arduino reset pin)
    Display(int8_t rst = -1);
    void init();

    Adafruit_SSD1306& operator() ();

    void drawText(const char* text);

private:
    uint8_t mWidth;
    uint8_t mHeight;
    Adafruit_SSD1306 mDisplay;

};