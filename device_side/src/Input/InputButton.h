#pragma once

#include <functional>


namespace input {
    enum class Action {
        NONE = 0,
        SINGLE_PRESS,
        DOUBLE_PRESS,
        TRIPLE_PRESS,
        LONG_PRESS,
    };

    using OnUserActionFunc = std::function<void(Action action)>;

    class Button {
    public:
        Button();

        void setCallback(const OnUserActionFunc& func = nullptr);
        void update();

    private:
        OnUserActionFunc mFunc{ nullptr };

        uint32_t mCountingStartTime{ 0 };
        uint32_t mLastDebounceTime{ 0 };
        uint8_t mPressesCount{ 0 };
        bool mCountingInProgress{ false };
        bool mLastButtonState{ true };

    };
}
