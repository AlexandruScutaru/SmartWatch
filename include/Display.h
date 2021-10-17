#pragma once

#include <Adafruit_SSD1306.h>

#include <memory>


class Display {
public:
    Display(uint8_t w, uint8_t h, int8_t rst);

    virtual void display() = 0;

    void init();
    void clear();
    void clearAndDisplay();
    void setCursor(int16_t x, int16_t y);
    void setTextSize(uint8_t size);
    void setTextColor(uint16_t color);
    void setTextColor(uint16_t color, uint16_t bg);
    void invert(bool invert);

    void drawPixel(int16_t x, int16_t y, uint16_t color = SSD1306_WHITE);
    void drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color = SSD1306_WHITE);
    void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color = SSD1306_WHITE);
    void drawBitmap(int16_t x, int16_t y, const uint8_t* bitmap, int16_t w, int16_t h, uint16_t color, uint16_t bg);

    size_t print(uint32_t);
    size_t print(int32_t);
    size_t print(double);
    size_t print(char);
    size_t print(unsigned char);
    size_t print(const char*);
    size_t print(const String&);

    size_t println(uint32_t);
    size_t println(int32_t);
    size_t println(double);
    size_t println(char);
    size_t println(unsigned char);
    size_t println(const char*);
    size_t println(const String&);
    size_t println();

    virtual ~Display() {}

protected:
    Adafruit_SSD1306 mDisplay;
};

using DisplayPtr = std::shared_ptr<Display>;
