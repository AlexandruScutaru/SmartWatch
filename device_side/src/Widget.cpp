#include "Widget.h"


Widget::Widget() {}

Widget::~Widget() {}

void Widget::handle(Input::Action action) {
    switch (action)
    {
        case Input::Action::SINGLE_TAP:
            onSingleTap();
            break;
        case Input::Action::DOUBLE_TAP:
            onDoubleTap();
            break;
        case Input::Action::TRIPLE_TAP:
            onTripleTap();
            break;
        case Input::Action::LONG_HOLD:
            onLongPress();
            break;
        default:
            //no op
            break;
    }
}
