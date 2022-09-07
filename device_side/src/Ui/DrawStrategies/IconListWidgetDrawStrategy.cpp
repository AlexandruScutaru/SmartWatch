#include "IconListWidgetDrawStrategy.h"

#include "Display/IDisplay.h"
#include "Utils/Vector.h"
#include "Ui/Controls/Widget.h"
#include "Utils/ColorUtils.h"


void IconListWidgetDrawStrategy::drawList(DisplayPtr display, const vec2& pos, const vec2& size, const vector<WidgetPtr>& list, size_t currentItemIdx) {
    size_t itemCount = list.size();
    size_t entriesToBeDrawn = 1;

    //slot 1
    if (itemCount > 1 && currentItemIdx) {
        if (const auto& item = list[currentItemIdx - 1]) {
            item->drawAt(display, vec2(pos.x + 2, 16 + (size.y - 4 - 20) / 2));
        }
    }

    //slot 2
    if (const auto& item = list[currentItemIdx]) {
        item->drawAt(display, vec2((size.x - 40) / 2, 16 + (size.y - 4 - 40) / 2));
    }

    //slot 3
    if (currentItemIdx != itemCount -1) {
        if (const auto& item = list[currentItemIdx + 1]) {
            item->drawAt(display, vec2(size.x - 22, 16 + (size.y - 4 - 20) / 2));
        }
    }

    //scrollbar
    if (itemCount <= entriesToBeDrawn) {
        return;
    }

    int16_t barWidth = entriesToBeDrawn / (double)itemCount * size.x;
    int16_t barPos = currentItemIdx / (double)itemCount * size.x;

    display->drawRect(pos.x, pos.y + size.y - 4, size.x, 4, color_utils::WHITE);
    display->fillRect(pos.x + barPos, pos.y + size.y - 3, barWidth, 2, color_utils::WHITE);
}
