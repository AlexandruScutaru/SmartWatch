#pragma once

#include "Display.h"

#include <memory>

class BLE;
using BLEPtr = std::shared_ptr<BLE>;

namespace input {
    enum class Action;
}

class IScreenState {
public:    
    virtual void handle(input::Action action) = 0;
    virtual void update(double dt) = 0;
    virtual void draw(DisplayPtr display) = 0;
};


class ScreenStateMachine {
public:
    ScreenStateMachine();
    ~ScreenStateMachine();

    void init(DisplayPtr display);

    void setState(std::shared_ptr<IScreenState> state);
    std::shared_ptr<IScreenState> getCurrentState();

    void handle(input::Action action);
    void update(double dt);
    void draw();
    void changeState(std::shared_ptr<IScreenState> state);

    void setBle(BLEPtr mBle);
    //quick way to get some data via a button action
    void sendData(const std::string& data);

private:
    std::shared_ptr<IScreenState> mCurrentState;
    DisplayPtr mDisplay;
    BLEPtr mBle;

};
