#pragma once

#include "Widget.h"

class Button : public Widget {
public:
    Button();

    void update(double dt) override;
    void draw(DisplayPtr display) override;

    void onSingleTap() override;
    void onDoubleTap() override;
    void onTripleTap() override;
    void onLongPress() override;

private:

};