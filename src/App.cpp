#include "App.h"

#include "ScreenStateMachine.h"
#include "IdleState.h"
#include "MainScreenState.h"
#include "Ota.h"

#define PIN_VIBRATION_MOTOR 16
#define PIN_BUTTON_INPUT    4
#define PIN_BATTERY_LEVEL   33

#define TARGET_FPS          30
#define TARGET_FRAME_TICKS  (1000 / TARGET_FPS)


//TODO:
/*
    implement minimal GUI system with control events
    implement timer logic
    implemnet messaging system
*/

App::App() 
    : mDisplay(Display())
    , mInput(Input(PIN_BUTTON_INPUT))
{
    pinMode(PIN_VIBRATION_MOTOR, OUTPUT);
    digitalWrite(PIN_VIBRATION_MOTOR, HIGH);
    pinMode(PIN_BUTTON_INPUT, INPUT_PULLUP);
    pinMode(PIN_BATTERY_LEVEL, INPUT);
  
    Serial.begin(115200);
    Serial.println("Booting");
  
    OTA::init();
    mInput.init();
    mDisplay.init();

    // Show initial display buffer contents on the screen --
    // the library initializes this with an Adafruit splash screen.
    mDisplay().display();
    delay(2000);
    mDisplay().clearDisplay();
    mDisplay().display();

    mScreenStateMachine.setState(std::shared_ptr<IScreenState>(new MainScreenState(&mScreenStateMachine)));

    Serial.println("Setup done");

}

App::~App() {}


void App::run() {
    mTimer.start(2000, false, [](){
        static bool running = false;
        if (running) {
            digitalWrite(PIN_VIBRATION_MOTOR, HIGH);
        } else {
            digitalWrite(PIN_VIBRATION_MOTOR, LOW);
        }
        running = !running;
    });

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

    mTimer.update();
}

void App::draw() {
    mScreenStateMachine.draw(mDisplay);
}
