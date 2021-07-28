# SmartWatch-MicrocontrollerSide
Basic smart watch based on the ESP32 microcontroller.

This repo holds only the code that runs on the microcontroller. 
Another repo might be added to hold an eventual mobile app used to control it.

<img src="https://github.com/AlexandruScutaru/SmartWatch-MicrocontrollerSide/blob/master/resources/watch.png" width="500">

## Specifications:

- vibration motor controlled via a signal connected to a simple transistor switch
- one push button to navigate menu (single press, double press, long press etc)
- pin used to read the battery level
- charging/programming interface (being wifi enabled programming can be also done OTA via it's IP)

## More info

For now it is using the Arduino framework for ESP32, thinking of migrating to Espressif framework once I get more confortable with the device.
Using an RTOS is also in planning.
