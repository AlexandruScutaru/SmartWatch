#pragma once

#include <string>
#include <memory>


class IDisplay {
public:
    virtual ~IDisplay() = default;

    virtual void init() = 0;
    virtual void clear() = 0;
    virtual void display() = 0;
    virtual void clearAndDisplay() = 0;
    virtual void setCursor(int16_t x, int16_t y) = 0;
    virtual void setTextSize(uint8_t size) = 0;
    virtual void setTextColor(uint16_t color) = 0;
    virtual void setTextColor(uint16_t color, uint16_t bg) = 0;
    virtual void invert(bool invert) = 0;

    virtual void drawPixel(int16_t x, int16_t y, uint16_t color) = 0;
    virtual void drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) = 0;
    virtual void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) = 0;
    virtual void drawBitmap(int16_t x, int16_t y, const uint8_t* bitmap, int16_t w, int16_t h, uint16_t color, uint16_t bg) = 0;

    virtual size_t print(uint32_t value) = 0;
    virtual size_t print(int32_t value) = 0;
    virtual size_t print(double value) = 0;
    virtual size_t print(char value) = 0;
    virtual size_t print(unsigned char value) = 0;
    virtual size_t print(const char* value) = 0;
    virtual size_t print(const std::string& value) = 0;

    virtual size_t println(uint32_t value) = 0;
    virtual size_t println(int32_t value) = 0;
    virtual size_t println(double value) = 0;
    virtual size_t println(char value) = 0;
    virtual size_t println(unsigned char value) = 0;
    virtual size_t println(const char* value) = 0;
    virtual size_t println(const std::string& value) = 0;
    virtual size_t println() = 0;

};

using DisplayPtr = std::shared_ptr<IDisplay>;
