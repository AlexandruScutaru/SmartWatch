#pragma once

#include "Display.h"


class SerialDisplay : public Display{
public:
    SerialDisplay(uint8_t w, uint8_t h, int8_t rst);

    void display() override;

};
