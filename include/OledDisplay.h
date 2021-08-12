#pragma once

#include "IDisplay.h"

#include <Adafruit_SSD1306.h>


class OledDisplay : public IDisplay{
public:
    //Reset pin # (or -1 if sharing Arduino reset pin)
    OledDisplay(int8_t rst = -1);

    void init() override;
    void clear() override;
    void display() override;
    void clearAndDisplay() override;
    void setCursor(int16_t x, int16_t y) override;
    void setTextSize(uint8_t size) override;
    void setTextColor(uint16_t color) override;
    void invert(bool invert) override;

    void drawRect(int16_t x, int16_t y, int16_t w, int16_t h) override;
    void fillRect(int16_t x, int16_t y, int16_t w, int16_t h) override;

    size_t print(uint32_t val) override;
    size_t print(int32_t val) override;
    size_t print(double val) override;
    size_t print(char val) override;
    size_t print(unsigned char val) override;
    size_t print(const char* val) override;
    size_t print(const String& val) override;

    size_t println(uint32_t val) override;
    size_t println(int32_t val) override;
    size_t println(double val) override;
    size_t println(char val) override;
    size_t println(unsigned char val) override;
    size_t println(const char* val) override;
    size_t println(const String& val) override;
    size_t println() override;

private:
    uint8_t mWidth;
    uint8_t mHeight;
    Adafruit_SSD1306 mDisplay;

};
