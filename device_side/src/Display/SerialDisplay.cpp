#include "SerialDisplay.h"

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>


SerialDisplay::SerialDisplay(uint8_t w, uint8_t h, int8_t rst)
    : OledDisplay(w, h, rst)
    , mBuffLen(w * ((h + 7) / 8))
    , mWebSocket(web::WebSocket(81, web::WebSocketCallbacks()))
{}


void SerialDisplay::display() {
#ifdef WRITE_SERIAL_DISPLAY
    auto buffer = mDisplay.getBuffer();
    if (buffer) {
        mWebSocket.update();
        mWebSocket.broadcast(buffer, mBuffLen);
    }
#endif
}
