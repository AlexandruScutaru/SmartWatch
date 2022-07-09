#include "App.h"

#include "ScreenStateMachine.h"
#include "IdleState.h"
#include "MainScreenState.h"
#include "Ota.h"
#include "ClockFace.h"
#include "Logger.h"
#include "BleCharacteristicsHelper.h"
#include "BleServerHelper.h"
#include "WebSocket.h"
#include "credentials.h"

#if defined(SERIAL_DISPLAY)
    #include "SerialDisplay.h"
#else
    #include "OledDisplay.h"
#endif

#include <WiFi.h>

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
    Serial.begin(115200);
    while(!Serial);

#if defined(SERIAL_DISPLAY)
    mDisplay = std::make_shared<SerialDisplay>(128, 64, -1);
#else
    mDisplay = std::make_shared<OledDisplay>(128, 64, -1);
#endif
    mDisplay->init();

    initWifi();
    initLogger();

    LOG_LN("Booting");

    pinMode(PIN_VIBRATION_MOTOR, OUTPUT);
    digitalWrite(PIN_VIBRATION_MOTOR, HIGH);
    pinMode(PIN_BATTERY_LEVEL, INPUT);

    OTA::init();


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

void App::initWifi() {
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_NAME, WIFI_PASS);
    while (WiFi.waitForConnectResult() != WL_CONNECTED) {
        Serial.println("Connection Failed! Rebooting...");
        delay(5000);
        ESP.restart();
    }

    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    mDisplay->setCursor(0, 0);

    mDisplay->clear();
    mDisplay->print(WiFi.localIP().toString());
    delay(2000);
}

void App::initLogger() {
#if defined(SERIAL_LOGGER) && defined(WS_LOGGER)
    // if for some reason both are enabled fallback to serial logger only, only one works at a time
    #undef WS_LOGGER
#endif

#if defined(SERIAL_LOGGER)
    logging::initSerialLogger();
#elif defined(WS_LOGGER)
    mLoggerWebSocket = logging::initWebSocketLogger();
#endif
}

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
        LOG_LN(data);
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
    if (mLoggerWebSocket) {
        mLoggerWebSocket->update();
    }

    OTA::handle();
    mInputButton.update();
    mScreenStateMachine.update(delta);
    CLOCK_FACE.update(delta);
}

void App::draw() {
    mScreenStateMachine.draw();
}

void App::onUserAction(input::Action action) {
    LOG_LN("inputAction " << static_cast<int>(action));
    mScreenStateMachine.handle(action);
}
