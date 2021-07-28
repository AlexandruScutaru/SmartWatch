#include "Display.h"

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>


Display::Display(int8_t rst/*= -1*/) 
    : mWidth(128)
    , mHeight(32)
    , mDisplay(mWidth, mHeight, &Wire, rst)  // Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
{}

void Display::init() {
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

Adafruit_SSD1306& Display::operator() () {
    return mDisplay;
}

void Display::drawText(const char* text) {
    mDisplay.clearDisplay();
    mDisplay.setCursor(0,0);
    mDisplay.println(text);
    mDisplay.display();
}