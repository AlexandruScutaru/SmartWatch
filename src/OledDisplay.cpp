#include "OledDisplay.h"

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>


OledDisplay::OledDisplay(uint8_t w, uint8_t h, int8_t rst)
    : Display(w, h, rst)
{}


void OledDisplay::display() {
    mDisplay.display();
}
