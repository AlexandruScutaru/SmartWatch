#include "Input.h"

#include <Arduino.h>

Input::Input(int buttonPin)
    : buttonPin(buttonPin) 
{}

void Input::init() {
    // Button timing variable
    debounce = 20;            
    DCgap = 250;              
    holdTime = 1000;          
    longHoldTime = 3000;
  
    // Button variables
    buttonPin;
    buttonVal = HIGH;         
    buttonLast = HIGH;        
    DCwaiting = false;        
    DConUp = false;           
    singleOK = true;          
    downTime = -1;            
    upTime = -1;              
    ignoreUp = false;         
    waitForUp = false;        
    holdEventPast = false;    
    longHoldEventPast = false;
}

Input::Action Input::getUserAction() {    
   Action action = Action::NONE;
   buttonVal = digitalRead(buttonPin);
   // Button pressed down
   if (buttonVal == LOW && buttonLast == HIGH && (millis() - upTime) > debounce)
   {
       downTime = millis();
       ignoreUp = false;
       waitForUp = false;
       singleOK = true;
       holdEventPast = false;
       longHoldEventPast = false;
       if ((millis()-upTime) < DCgap && DConUp == false && DCwaiting == true)  DConUp = true;
       else  DConUp = false;
       DCwaiting = false;
   }
   // Button released
   else if (buttonVal == HIGH && buttonLast == LOW && (millis() - downTime) > debounce)
   {        
       if (!ignoreUp)
       {
           upTime = millis();
           if (DConUp == false) DCwaiting = true;
           else
           {
               action = Action::DOUBLE_TAP;
               DConUp = false;
               DCwaiting = false;
               singleOK = false;
           }
       }
   }
   // Test for normal click event: DCgap expired
   if ( buttonVal == HIGH && (millis()-upTime) >= DCgap && DCwaiting == true && DConUp == false && singleOK == true && action != Action::DOUBLE_TAP)
   {
       action = Action::SINGLE_TAP;
       DCwaiting = false;
   }
   // Test for hold
   if (buttonVal == LOW && (millis() - downTime) >= holdTime) {
       // Trigger "normal" hold
       if (not holdEventPast)
       {
           action = Action::HOLD;
           waitForUp = true;
           ignoreUp = true;
           DConUp = false;
           DCwaiting = false;
           //downTime = millis();
           holdEventPast = true;
       }
       // Trigger "long" hold
       if ((millis() - downTime) >= longHoldTime)
       {
           if (not longHoldEventPast)
           {
               action = Action::LONG_HOLD;
               longHoldEventPast = true;
           }
       }
   }
   buttonLast = buttonVal;
   return action;
}
