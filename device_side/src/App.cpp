#include "App.h"

#include "ScreenStateMachine.h"
#include "IdleState.h"
#include "MainScreenState.h"
#include "Ota.h"
#include "ClockFace.h"
#include "Logger.h"

//#define SERIAL_DISPLAY
#if defined(SERIAL_DISPLAY)
    #include "SerialDisplay.h"
#else
    #include "OledDisplay.h"
#endif

#define PIN_VIBRATION_MOTOR 16
#define PIN_BUTTON_INPUT    4
#define PIN_BATTERY_LEVEL   33

#define TARGET_FPS          20
#define TARGET_FRAME_TICKS  (1000 / TARGET_FPS)


//TODO:
/*
    implement minimal GUI system with control events
    implement timer logic
    implemnet messaging system
*/

App::App() 
    : mInput(Input(PIN_BUTTON_INPUT))
{
    pinMode(PIN_VIBRATION_MOTOR, OUTPUT);
    digitalWrite(PIN_VIBRATION_MOTOR, HIGH);
    pinMode(PIN_BUTTON_INPUT, INPUT_PULLUP);
    pinMode(PIN_BATTERY_LEVEL, INPUT);

    Serial.begin(115200);
    LOG_LN("Booting");

    OTA::init();
    mInput.init();

#if defined(SERIAL_DISPLAY)
    mDisplay = std::make_shared<SerialDisplay>(128, 64, -1);
#else
    mDisplay = std::make_shared<OledDisplay>(128, 64, -1);
#endif
    mDisplay->init();

    Callbacks bleCallbacks;
    bleCallbacks.write = [this](const std::string& data) { 
        bleOnWrite(data);
    };
    mBle = std::make_shared<BLE>("ESP32-Watch", bleCallbacks);

    mScreenStateMachine.init(mDisplay);
    mScreenStateMachine.setBle(mBle);

    // Show initial display buffer contents on the screen --
    // the library initializes this with an Adafruit splash screen.
    if (mDisplay) {
        mDisplay->display();
        delay(2000);
        mDisplay->clear();
        mDisplay->display();
    }

    mScreenStateMachine.setState(std::shared_ptr<IScreenState>(new MainScreenState(&mScreenStateMachine)));

    LOG_LN("Setup done");
}

App::~App() {}


void App::run() {
    mPrevTicks = millis();
    loop();
}

void App::loop() {
    for (;;) {
        mNewTicks = millis();
        mFrameTicks = mNewTicks - mPrevTicks;
        mPrevTicks = mNewTicks;
        delta =  mFrameTicks / double(TARGET_FRAME_TICKS);

        update(delta);
        draw();

        if(mFrameTicks < TARGET_FRAME_TICKS) {
            delay(TARGET_FRAME_TICKS - mFrameTicks);
        }
    }
}

void App::update(double delta) {
    /*
        handle ota
        get user input
        update current state controls based on user input
        handle state transitions based on predefined transitions
        draw current state controls 
    */

    OTA::handle();

    Input::Action userAction = mInput.getUserAction();
    mScreenStateMachine.handle(userAction);
    mScreenStateMachine.update(delta);
    CLOCK_FACE.update(delta);
}

void App::draw() {
    mScreenStateMachine.draw();
}


void App::bleOnWrite(const std::string& data) {
    LOG_LN(data.c_str());

    //just to get an indication that it works
    static bool motor = true;
    motor = !motor;
    digitalWrite(PIN_VIBRATION_MOTOR, static_cast<uint8_t>(motor));
}
