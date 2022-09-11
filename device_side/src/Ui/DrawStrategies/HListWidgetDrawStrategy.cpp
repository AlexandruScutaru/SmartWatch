#include "HListWidgetDrawStrategy.h"

#include "Display/IDisplay.h"
#include "Ui/Controls/Widget.h"
#include "Utils/ColorUtils.h"


void HListWidgetDrawStrategy::drawList(DisplayPtr display, const vec2& pos, const vec2& size, const std::vector<WidgetPtr>& list, size_t currentItemIdx) {
    size_t itemCount = list.size();
    size_t entriesToBeDrawn = 1;

    if (const auto& item = list[currentItemIdx]) {
        item->drawAt(display, vec2(pos.x, pos.y));
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
