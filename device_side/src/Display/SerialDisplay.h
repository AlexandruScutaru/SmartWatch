#pragma once

#include "OledDisplay.h"

#include "Web/WebSocket.h"


class SerialDisplay : public OledDisplay {
public:
    SerialDisplay(uint8_t w, uint8_t h, int8_t rst);

    void display() override;

private:
    uint16_t mBuffLen = 0;
    web::WebSocket mWebSocket;

};
