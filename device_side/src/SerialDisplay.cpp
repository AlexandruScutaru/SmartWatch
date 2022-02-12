#include "SerialDisplay.h"

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>


SerialDisplay::SerialDisplay(uint8_t w, uint8_t h, int8_t rst)
    : Display(w, h, rst)
    , mBuffLen(w * ((h + 7) / 8))
{}


void SerialDisplay::display() {
#ifdef WRITE_SERIAL_DISPLAY
    auto buffer = mDisplay.getBuffer();
    if (buffer) {
        Serial.print("<b>");
        Serial.write(buffer, mBuffLen);
        Serial.println("</b>");
    }
#endif
}
