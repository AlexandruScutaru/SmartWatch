#pragma once


class OTA {
public:
    static bool init();
    static void handle();

private:
    OTA() {}
    static char ssid[32];
    static char pass[32];

    static void getWifiCredentials();

};