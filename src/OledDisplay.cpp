#include "OledDisplay.h"

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>


OledDisplay::OledDisplay(int8_t rst /*= -1*/)
    : mWidth(128)
    , mHeight(64)
    , mDisplay(mWidth, mHeight, &Wire, rst)  // Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
{}

void OledDisplay::init() {
    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    if(!mDisplay.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
        Serial.println("SSD1306 allocation failed");
        delay(2000);
        ESP.restart();
    }

    //set some default display properties
    mDisplay.setTextSize(1);                  // Normal 1:1 pixel scale
    mDisplay.setTextColor(SSD1306_WHITE);     // Draw white text
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
    mDisplay.clearDisplay();
    mDisplay.display();
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

void OledDisplay::invert(bool invert) {
    mDisplay.invertDisplay(invert);
}


void OledDisplay::drawRect(int16_t x, int16_t y, int16_t w, int16_t h) {
    mDisplay.drawRect(x, y, w, h, SSD1306_WHITE);
};

void OledDisplay::fillRect(int16_t x, int16_t y, int16_t w, int16_t h) {
    mDisplay.fillRect(x, y, w, h, SSD1306_WHITE);
};


size_t OledDisplay::print(uint32_t val) {
    return mDisplay.print(val);
}

size_t OledDisplay::print(int32_t val) {
    return mDisplay.print(val);
}

size_t OledDisplay::print(double val) {
    return mDisplay.print(val);
}

size_t OledDisplay::print(char val) {
    return mDisplay.print(val);
}

size_t OledDisplay::print(unsigned char val) {
    return mDisplay.print(val);
}

size_t OledDisplay::print(const char* val) {
    return mDisplay.print(val);
}

size_t OledDisplay::print(const String& val) {
    return mDisplay.print(val);
}


size_t OledDisplay::println(uint32_t val) {
    return mDisplay.println(val);
}

size_t OledDisplay::println(int32_t val) {
    return mDisplay.println(val);
}

size_t OledDisplay::println(double val) {
    return mDisplay.println(val);
}

size_t OledDisplay::println(char val) {
    return mDisplay.println(val);
}

size_t OledDisplay::println(unsigned char val) {
    return mDisplay.println(val);
}

size_t OledDisplay::println(const char* val) {
    return mDisplay.println(val);
}

size_t OledDisplay::println(const String& val) {
    return mDisplay.println(val);
}

size_t OledDisplay::println() {
    return mDisplay.println();
}
