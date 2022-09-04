#pragma once

#include "Display/Display.h"
#include "Input/InputButton.h"
#include "Ui/Views/StackView.h"
#include "Misc/EventTypes.h"

#include <cstdint>

namespace web {
    class WebSocket;
    using WebSocketPtr = std::shared_ptr<WebSocket>;
}

namespace ble {
    class Server;
    using ServerPtr = std::shared_ptr<Server>;
}

class App {
public:
    App();
    ~App();

    void run();

//events
    void onTestEvent(TestEvent& event);

private:
    void initWifi();
    void initLogger();
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
    StackView mStackView;
    ble::ServerPtr mBle;
    web::WebSocketPtr mLoggerWebSocket;

};
