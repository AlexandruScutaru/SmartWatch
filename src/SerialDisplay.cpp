#include "SerialDisplay.h"

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>


SerialDisplay::SerialDisplay(uint8_t w, uint8_t h, int8_t rst)
    : Display(w, h, rst)
{}


void SerialDisplay::display() {
    auto buffer = mDisplay.getBuffer();

    //send buffer via Serial to COM port
}
