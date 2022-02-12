#pragma once

#include "Display.h"
#include "InputButton.h"
#include "ScreenStateMachine.h"

#include <cstdint>


namespace ble {
    class Server;
    using ServerPtr = std::shared_ptr<Server>;
}

class App {
public:
    App();
    ~App();

    void run();

private:
    void initBle();

    void loop();
    void update(double delta);
    void draw();

    void onUserAction(input::Action action);

    //app loop varaibles
    uint32_t mPrevTicks = 0U;
    uint32_t mNewTicks = 0U;
    uint32_t mFrameTicks = 0U;
    double delta = 0.0;

    DisplayPtr mDisplay;
    input::Button mInputButton;
    ScreenStateMachine mScreenStateMachine;
    ble::ServerPtr mBle;
};
