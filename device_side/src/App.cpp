#include "App.h"

#include "ScreenStateMachine.h"
#include "IdleState.h"
#include "MainScreenState.h"
#include "Ota.h"
#include "ClockFace.h"
#include "Logger.h"
#include "BleCharacteristicsHelper.h"
#include "BleServerHelper.h"

#if defined(SERIAL_DISPLAY)
    #include "SerialDisplay.h"
#else
    #include "OledDisplay.h"
#endif

#define PIN_VIBRATION_MOTOR 16
#define PIN_BATTERY_LEVEL   33

#define TARGET_FPS          20
#define TARGET_FRAME_TICKS  (1000 / TARGET_FPS)


//TODO:
/*
    implement minimal GUI system with control events
    implement timer logic
    implemnet messaging system
*/

App::App() {

#ifdef SHOULD_LOG
    Serial.begin(115200);
    while(!Serial);
#endif

    LOG_LN("Booting");

    pinMode(PIN_VIBRATION_MOTOR, OUTPUT);
    digitalWrite(PIN_VIBRATION_MOTOR, HIGH);
    pinMode(PIN_BATTERY_LEVEL, INPUT);

    OTA::init();

#if defined(SERIAL_DISPLAY)
    mDisplay = std::make_shared<SerialDisplay>(128, 64, -1);
#else
    mDisplay = std::make_shared<OledDisplay>(128, 64, -1);
#endif
    mDisplay->init();

    initBle();

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

    mInputButton.setCallback([this](input::Action action) {
        onUserAction(action);
    });

    LOG_LN("Setup done");
}

App::~App() {}


void App::initBle() {
    ble::CharacteristicCallbacksArray bleCallbacks;
    bleCallbacks[index(ble::CharacteristicTypes::NOTIFICATION)].mWriteFunc = [this](const std::string& data) {
        //damn :))
        uint8_t value = String(data.c_str()).toInt();
        digitalWrite(PIN_VIBRATION_MOTOR, static_cast<uint8_t>(value == 0));
    };

    bleCallbacks[index(ble::CharacteristicTypes::WIFI_STATUS)].mReadFunc = [this](std::string& data) {
        data = "dummy status";
    };

    bleCallbacks[index(ble::CharacteristicTypes::TIME)].mWriteFunc = [this](const std::string& data) {
        LOG_LN(data.c_str());
    };

    auto bleCharacteristicsBuilder = ble::CharacteristicsBuilder(bleCallbacks);
    mBle = std::make_shared<ble::Server>("ESP32-Watch", bleCharacteristicsBuilder.getCharacteristics());
}

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
    OTA::handle();
    mInputButton.update();
    mScreenStateMachine.update(delta);
    CLOCK_FACE.update(delta);
}

void App::draw() {
    mScreenStateMachine.draw();
}

void App::onUserAction(input::Action action) {
    mScreenStateMachine.handle(action);
}
