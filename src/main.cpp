#include <Arduino.h>

#include "Ota.h"
#include "Display.h"
#include "Input.h"
#include "ScreenStateMachine.h"
#include "IdleState.h"
#include "MainScreenState.h"

#define PIN_VIBRATION_MOTOR 16
#define PIN_BUTTON_INPUT 4

int targetFrameTicks = 1000 / 30;
long prevTicks = 0;
long newTicks = 0;
long frameTicks = 0;
double delta = 0.0;

Display display;
Input input(PIN_BUTTON_INPUT);
ScreenStateMachine screenStateMachine;

//to do
/*
    implement minimal GUI system with control events
    implement timer logic
    implemnet messaging system
*/


void setup() {
    pinMode(PIN_VIBRATION_MOTOR, OUTPUT);
    digitalWrite(PIN_VIBRATION_MOTOR, HIGH);
    pinMode(PIN_BUTTON_INPUT, INPUT_PULLUP);
  
    Serial.begin(115200);
    Serial.println("Booting");
  
    input.init();
    OTA::init();
    display.init();

    // Show initial display buffer contents on the screen --
    // the library initializes this with an Adafruit splash screen.
    display().display();
    delay(2000);
    display().clearDisplay();
    display().display();

    screenStateMachine.setState(std::shared_ptr<IScreenState>(new MainScreenState(&screenStateMachine)));

    Serial.println("Setup done");

    prevTicks = millis();
}

void loop() {
    newTicks = millis();

    frameTicks = newTicks - prevTicks;
    prevTicks = newTicks;

    delta =  frameTicks / double(targetFrameTicks);

    //display().clearDisplay();
    //display().setCursor(0, 0);
    //display().println(frameTicks);
    //display().println(delta);
    //display().display();

    /*
    handle ota
    get user input
    update current state controls based on user input
    handle state transitions based on predefined transitions
    draw current state controls 
    */

    OTA::handle();
    
    Input::Action userAction = input.getUserAction();
 
    screenStateMachine.handle(userAction);
    screenStateMachine.getCurrentState()->update(delta);
    screenStateMachine.getCurrentState()->draw(display);

    /*
    switch (userAction) {
    case Input::Action::SINGLE_TAP:
        display.drawText("single tap");
        digitalWrite(PIN_VIBRATION_MOTOR, HIGH);
        break;
    case Input::Action::DOUBLE_TAP:
        display.drawText("double tap");
        digitalWrite(PIN_VIBRATION_MOTOR, LOW);
        break;
    case Input::Action::HOLD:
        display.drawText("hold");
        break;
    case Input::Action::LONG_HOLD:
        display.drawText("long hold");
        break;
    default:
        break;
    }
    */

    if(frameTicks < targetFrameTicks) {
        delay(targetFrameTicks - frameTicks);
    }
}
