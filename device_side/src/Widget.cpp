#include "Widget.h"
#include "InputButton.h"


Widget::Widget() {}

Widget::~Widget() {}

void Widget::handle(input::Action action) {
    switch (action)
    {
        case input::Action::SINGLE_PRESS:
            onSingleTap();
            break;
        case input::Action::DOUBLE_PRESS:
            onDoubleTap();
            break;
        case input::Action::TRIPLE_PRESS:
            onTripleTap();
            break;
        case input::Action::LONG_PRESS:
            onLongPress();
            break;
        default:
            //no op
            break;
    }
}
