#include "Display.h"

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>


Display::Display(uint8_t w, uint8_t h, int8_t rst)
    : mDisplay(w, h, &Wire, rst)  // Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
{}


void Display::init() {
    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    if(!mDisplay.begin(SSD1306_SWITCHCAPVCC)) {
        Serial.println("Display buffer allocation failed");
        delay(2000);
        ESP.restart();
    }

    //set some default display properties
    mDisplay.setTextSize(1);                  // Normal 1:1 pixel scale
    mDisplay.setTextColor(SSD1306_WHITE);     // Draw "white" text
    mDisplay.setCursor(0, 0);                 // Start at top-left corner
    mDisplay.cp437(true);                     // Use full 256 char 'Code Page 437' font
}

void Display::clear() {
    mDisplay.clearDisplay();
}

void Display::clearAndDisplay() {
    clear();
    display();
}

void Display::setCursor(int16_t x, int16_t y) {
    mDisplay.setCursor(x, y);
}

void Display::setTextSize(uint8_t size) {
    mDisplay.setTextSize(size);
}

void Display::setTextColor(uint16_t color) {
    mDisplay.setTextColor(color);
}

void Display::invert(bool invert) {
    mDisplay.invertDisplay(invert);
}

void Display::drawPixel(int16_t x, int16_t y) {
    mDisplay.drawPixel(x, y, SSD1306_WHITE);
}

void Display::drawRect(int16_t x, int16_t y, int16_t w, int16_t h) {
    mDisplay.drawRect(x, y, w, h, SSD1306_WHITE);
};

void Display::fillRect(int16_t x, int16_t y, int16_t w, int16_t h) {
    mDisplay.fillRect(x, y, w, h, SSD1306_WHITE);
};


size_t Display::print(uint32_t val) {
    return mDisplay.print(val);
}

size_t Display::print(int32_t val) {
    return mDisplay.print(val);
}

size_t Display::print(double val) {
    return mDisplay.print(val);
}

size_t Display::print(char val) {
    return mDisplay.print(val);
}

size_t Display::print(unsigned char val) {
    return mDisplay.print(val);
}

size_t Display::print(const char* val) {
    return mDisplay.print(val);
}

size_t Display::print(const String& val) {
    return mDisplay.print(val);
}


size_t Display::println(uint32_t val) {
    return mDisplay.println(val);
}

size_t Display::println(int32_t val) {
    return mDisplay.println(val);
}

size_t Display::println(double val) {
    return mDisplay.println(val);
}

size_t Display::println(char val) {
    return mDisplay.println(val);
}

size_t Display::println(unsigned char val) {
    return mDisplay.println(val);
}

size_t Display::println(const char* val) {
    return mDisplay.println(val);
}

size_t Display::println(const String& val) {
    return mDisplay.println(val);
}

size_t Display::println() {
    return mDisplay.println();
}
