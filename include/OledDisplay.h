#pragma once

#include "Display.h"


class OledDisplay : public Display {
public:
    OledDisplay(uint8_t w, uint8_t h, int8_t rst);

    void display() override;

};
