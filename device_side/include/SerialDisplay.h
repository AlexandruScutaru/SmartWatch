#pragma once

#include "Display.h"
#include "WebSocket.h"


class SerialDisplay : public Display {
public:
    SerialDisplay(uint8_t w, uint8_t h, int8_t rst);

    void display() override;

private:
    uint16_t mBuffLen = 0;
    web::WebSocket mWebSocket;

};
