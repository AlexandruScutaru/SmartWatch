#include "Ota.h"
#include "Logger.h"
#include "credentials.h"

#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>


bool OTA::init() {
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_NAME, WIFI_PASS);
    while (WiFi.waitForConnectResult() != WL_CONNECTED) {
        LOG_LN("Connection Failed! Rebooting...");
        delay(5000);
        ESP.restart();
    }

    ArduinoOTA
        .onStart([]() {
            String type;
            if (ArduinoOTA.getCommand() == U_FLASH)
                type = "sketch";
            else // U_SPIFFS
                type = "filesystem";

            // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
            LOG_LN("Start updating " + type);
        })
        .onEnd([]() {
            LOG_LN("\nEnd");
        })
        .onProgress([](unsigned int progress, unsigned int total) {
            LOG_FMT("Progress: %u%%\r", (progress / (total / 100)));
        })
        .onError([](ota_error_t error) {
            LOG_FMT("Error[%u]: ", error);
            if (error == OTA_AUTH_ERROR) LOG_LN("Auth Failed");
            else if (error == OTA_BEGIN_ERROR) LOG_LN("Begin Failed");
            else if (error == OTA_CONNECT_ERROR) LOG_LN("Connect Failed");
            else if (error == OTA_RECEIVE_ERROR) LOG_LN("Receive Failed");
            else if (error == OTA_END_ERROR) LOG_LN("End Failed");
        });

    ArduinoOTA.begin();

    LOG_LN("Ready");
    LOG("IP address: ");
    LOG_LN(WiFi.localIP());

    return true;
}

void OTA::handle() {
    ArduinoOTA.handle();
}
