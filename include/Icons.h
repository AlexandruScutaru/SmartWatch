#pragma once

#include <cstdint>


enum class Icon {
    SETTINGS,
    GAMES,
    CHECK_MARK,
};

class Icons {
public:
    static const uint8_t* getIcon8(Icon icon);
    static const uint8_t* getIcon16(Icon icon);
    static const uint8_t* getIcon32(Icon icon);

private:
    Icons() {}

    using icon8_t = uint8_t[8];
    static icon8_t mIcons8[];

    using icon16_t = uint8_t[32];
    static icon16_t mIcons16[];

    using icon32_t = uint8_t[128];
    static icon32_t mIcons32[];

};
