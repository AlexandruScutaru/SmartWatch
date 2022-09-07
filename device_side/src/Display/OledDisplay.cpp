#include "OledDisplay.h"

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>


OledDisplay::OledDisplay(uint8_t w, uint8_t h, int8_t rst)
    : mDisplay(w, h, &Wire, rst)  // Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
{}


void OledDisplay::init() {
    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    if (!mDisplay.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        delay(2000);
        ESP.restart();
    }

    //set some default display properties
    mDisplay.setTextSize(1);                  // Normal 1:1 pixel scale
    mDisplay.setTextColor(SSD1306_WHITE);     // Draw "white" text
    mDisplay.setCursor(0, 0);                 // Start at top-left corner
    mDisplay.cp437(true);                     // Use full 256 char 'Code Page 437' font
}

void OledDisplay::clear() {
    mDisplay.clearDisplay();
}

void OledDisplay::display() {
    mDisplay.display();
}

void OledDisplay::clearAndDisplay() {
    clear();
    display();
}

void OledDisplay::setCursor(int16_t x, int16_t y) {
    mDisplay.setCursor(x, y);
}

void OledDisplay::setTextSize(uint8_t size) {
    mDisplay.setTextSize(size);
}

void OledDisplay::setTextColor(uint16_t color) {
    mDisplay.setTextColor(color);
}

void OledDisplay::setTextColor(uint16_t color, uint16_t bg) {
    mDisplay.setTextColor(color, bg);
}

void OledDisplay::invert(bool invert) {
    mDisplay.invertDisplay(invert);
}

void OledDisplay::drawPixel(int16_t x, int16_t y, uint16_t color) {
    mDisplay.drawPixel(x, y, color);
}

void OledDisplay::drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
    mDisplay.drawRect(x, y, w, h, color);
}

void OledDisplay::fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
    mDisplay.fillRect(x, y, w, h, color);
}

void OledDisplay::drawBitmap(int16_t x, int16_t y, const uint8_t* bitmap, int16_t w, int16_t h, uint16_t color, uint16_t bg) {
    mDisplay.drawBitmap(x, y, bitmap, w, h, color, bg);
}

size_t OledDisplay::print(uint32_t value) {
    return mDisplay.print(value);
}

size_t OledDisplay::print(int32_t value) {
    return mDisplay.print(value);
}

size_t OledDisplay::print(double value) {
    return mDisplay.print(value);
}

size_t OledDisplay::print(char value) {
    return mDisplay.print(value);
}

size_t OledDisplay::print(unsigned char value) {
    return mDisplay.print(value);
}

size_t OledDisplay::print(const char* value) 
{
    return mDisplay.print(value);
}

size_t OledDisplay::print(const std::string& value) {
    return mDisplay.print(value.c_str());
}

size_t OledDisplay::println(uint32_t value) {
    return mDisplay.println(value);
}

size_t OledDisplay::println(int32_t value) {
    return mDisplay.println(value);
}

size_t OledDisplay::println(double value) {
    return mDisplay.println(value);
}

size_t OledDisplay::println(char value) {
    return mDisplay.println(value);
}

size_t OledDisplay::println(unsigned char value) {
    return mDisplay.println(value);
}

size_t OledDisplay::println(const char* value) {
    return mDisplay.println(value);
}

size_t OledDisplay::println(const std::string& value) {
    return mDisplay.println(value.c_str());
}

size_t OledDisplay::println() {
    return mDisplay.println();
}
