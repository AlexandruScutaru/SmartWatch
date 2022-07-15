#pragma once

#include <cstdint>


namespace icons {
    enum class IconType {
        UNKNOWN,
        SETTINGS,
        GAMES,
        CHECK_MARK,
    };

    const uint8_t* const getIcon8(IconType icon);
    const uint8_t* const getIcon16(IconType icon);
    const uint8_t* const getIcon32(IconType icon);
};
