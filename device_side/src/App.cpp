#include "App.h"

#include "Ota/Ota.h"
#include "Bluetooth/BleCharacteristicsHelper.h"
#include "Bluetooth/BleServerHelper.h"
#include "Web/WebSocket.h"
#include "credentials.h"
#include "Misc/TimeData.h"
#include "Misc/Logger.h"
#include "Misc/BatteryLevelReader.h"
#include "Misc/EventBus.h"
#include "Misc/EventTypes.h"


#if defined(SERIAL_DISPLAY)
    #include "Display/SerialDisplay.h"
#else
    #include "Display/OledDisplay.h"
#endif

#include <WiFi.h>

#define PIN_VIBRATION_MOTOR 16
#define PIN_BATTERY_LEVEL   33

#define TARGET_FPS          20
#define TARGET_FRAME_TICKS  (1000 / TARGET_FPS)


App::App() {
    pinMode(PIN_VIBRATION_MOTOR, OUTPUT);
    digitalWrite(PIN_VIBRATION_MOTOR, HIGH);
    pinMode(PIN_BATTERY_LEVEL, INPUT);

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

    OTA::init();
    //initBle();

    mStackView.init(mDisplay);

    mInputButton.setCallback([this](input::Action action) {
        onUserAction(action);
    });

    EVENT_BUS.subscribe<App, TestEvent>(this, &App::onTestEvent);

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
    mDisplay->display();
    delay(2000); // give some time to see what IP was assigned to it
}

void App::initLogger() {
#if defined(SERIAL_LOGGER) && defined(WS_LOGGER)
    // if for some reason both are enabled fallback to serial logger only, only one works at a time
    #undef WS_LOGGER
#endif

#if defined(SERIAL_LOGGER)
    logging::initSerialLogger();
    LOG_LN("serial logger inited");
#elif defined(WS_LOGGER)
    mLoggerWebSocket = logging::initWebSocketLogger();
    LOG_LN("websocket logger inited");
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
    mStackView.update(delta);
    CLOCK_TIME.update(delta);
    BATTERY_LEVEL_READER.update(delta);
}

void App::draw() {
    mStackView.draw();
}

void App::onUserAction(input::Action action) {
    LOG_LN("user input action: " << static_cast<int>(action));
    mStackView.handle(action);
}

//events
void App::onTestEvent(TestEvent& event) {
    LOG_LN("got event TestEvent::data: " << event.data);
}
