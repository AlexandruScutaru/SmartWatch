#pragma once

#include "Widget.h"

class Checkbox : public Widget {
public:
    Checkbox();

    void update(double dt) override;
    void draw(DisplayPtr display) override;

    void onSingleTap() override;
    void onDoubleTap() override;
    void onTripleTap() override;
    void onLongPress() override;

private:

};