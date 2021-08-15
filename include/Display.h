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
    void invert(bool invert);

    void drawPixel(int16_t x, int16_t y);
    void drawRect(int16_t x, int16_t y, int16_t w, int16_t h);
    void fillRect(int16_t x, int16_t y, int16_t w, int16_t h);

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
