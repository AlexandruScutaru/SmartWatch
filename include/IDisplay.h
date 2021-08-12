#pragma once

#include <cstdint>
#include <cstddef>
#include <memory>


class String;

class IDisplay {
public:

    virtual void init() = 0;
    virtual void clear() = 0;
    virtual void display() = 0;
    virtual void clearAndDisplay() = 0;
    virtual void setCursor(int16_t x, int16_t y) = 0;
    virtual void setTextSize(uint8_t size) = 0;
    virtual void setTextColor(uint16_t color) = 0;
    virtual void invert(bool invert) = 0;

    virtual void drawRect(int16_t x, int16_t y, int16_t w, int16_t h) = 0;
    virtual void fillRect(int16_t x, int16_t y, int16_t w, int16_t h) = 0;

    virtual size_t print(uint32_t) = 0;
    virtual size_t print(int32_t) = 0;
    virtual size_t print(double) = 0;
    virtual size_t print(char) = 0;
    virtual size_t print(unsigned char) = 0;
    virtual size_t print(const char*) = 0;
    virtual size_t print(const String&) = 0;

    virtual size_t println(uint32_t) = 0;
    virtual size_t println(int32_t) = 0;
    virtual size_t println(double) = 0;
    virtual size_t println(char) = 0;
    virtual size_t println(unsigned char) = 0;
    virtual size_t println(const char*) = 0;
    virtual size_t println(const String&) = 0;
    virtual size_t println() = 0;

    virtual ~IDisplay() {}

};

using IDisplayPtr = std::shared_ptr<IDisplay>;
