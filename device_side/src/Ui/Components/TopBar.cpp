#include "TopBar.h"


void TopBar::draw(DisplayPtr display) {
    mBatteryIndicator.draw(display);
}

void TopBar::update(double dt) {
    mBatteryIndicator.update(dt);
}
