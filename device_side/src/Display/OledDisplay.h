#pragma once

#include "IDisplay.h"

#include <Adafruit_SSD1306.h>


class OledDisplay : public IDisplay {
public:
    OledDisplay(uint8_t w, uint8_t h, int8_t rst);
    virtual ~OledDisplay() = default;

    void init() override;
    void clear() override;
    virtual void display() override;
    void clearAndDisplay() override;
    void setCursor(int16_t x, int16_t y) override;
    void setTextSize(uint8_t size) override;
    void setTextColor(uint16_t color) override;
    void setTextColor(uint16_t color, uint16_t bg) override;
    void invert(bool invert) override;

    void drawPixel(int16_t x, int16_t y, uint16_t color) override;
    void drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) override;
    void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) override;
    void drawBitmap(int16_t x, int16_t y, const uint8_t* bitmap, int16_t w, int16_t h, uint16_t color, uint16_t bg) override;

    size_t print(uint32_t value) override;
    size_t print(int32_t value) override;
    size_t print(double value) override;
    size_t print(char value) override;
    size_t print(unsigned char value) override;
    size_t print(const char* value) override;
    size_t print(const std::string& value) override;

    size_t println(uint32_t value) override;
    size_t println(int32_t value) override;
    size_t println(double value) override;
    size_t println(char value) override;
    size_t println(unsigned char value) override;
    size_t println(const char* value) override;
    size_t println(const std::string& value) override;
    size_t println() override;

protected:
    Adafruit_SSD1306 mDisplay;

};
