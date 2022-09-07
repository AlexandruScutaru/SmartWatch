#include "VListWidgetDrawStrategy.h"

#include "Display/IDisplay.h"
#include "Utils/Vector.h"
#include "Ui/Controls/Widget.h"
#include "Utils/ColorUtils.h"


void VListWidgetDrawStrategy::drawList(DisplayPtr display, const vec2& pos, const vec2& size, const vector<WidgetPtr>& list, size_t currentItemIdx) {
    size_t itemCount = list.size();
    size_t entriesToBeDrawn = 0;
    if (list[0]) {
        entriesToBeDrawn = size.y / list[0]->getSize().y;
    }

    size_t start = 0;
    if (itemCount < entriesToBeDrawn) {
        entriesToBeDrawn = itemCount;
    } else {
        if (currentItemIdx > entriesToBeDrawn / 2) {
            start = currentItemIdx - entriesToBeDrawn / 2;
            if (itemCount - start < entriesToBeDrawn) {
                start = itemCount - entriesToBeDrawn;
            }
        }
    }

    for (int i = 0; i < entriesToBeDrawn; i++) {
        if (const auto& item = list[i + start]) {
            item->drawAt(display, vec2(pos.x, i * item->getSize().y + pos.y));
        }
    }

    //scrollbar
    if (itemCount <= entriesToBeDrawn) {
        return;
    }

    int16_t barHeight = entriesToBeDrawn / (double)itemCount * size.y;
    int16_t barPos = start / (double)itemCount * size.y;

    display->drawRect(size.x - 4, pos.y, 4, size.y, color_utils::WHITE);
    display->fillRect(size.x - 3, pos.y + barPos, 2, barHeight, color_utils::WHITE);
}
