# Microcontroller Side
Basic smart watch based on the ESP32 microcontroller.

<img src="https://github.com/AlexandruScutaru/SmartWatch-MicrocontrollerSide/blob/master/doc_resources/watch.png" width="30%">
<img src="https://github.com/AlexandruScutaru/SmartWatch-MicrocontrollerSide/blob/master/doc_resources/serial_display.gif" width="55%">

## Specifications:

- vibration motor controlled via a signal connected to a simple transistor switch
- one push button to navigate menu (single press, double press, long press etc)
- pin used to read the battery level
- charging/programming interface (being wifi enabled programming can be also done OTA via it's IP)

## More info

For now it is using the Arduino framework for ESP32, thinking of migrating to Espressif framework once I get more confortable with the device.
Using an RTOS is also in planning.

# Mobile App
## iOS
Used to connect to the watch and control it (set time, send notification info, etc).

<img src="https://github.com/AlexandruScutaru/SmartWatch-MicrocontrollerSide/blob/master/doc_resources/ios_app.png" width="30%">
