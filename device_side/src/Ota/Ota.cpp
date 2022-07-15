#include "Ota.h"

#include "Misc/Logger.h"

#include <ArduinoOTA.h>


bool OTA::init() {
    ArduinoOTA
        .onStart([]() {
            String type;
            if (ArduinoOTA.getCommand() == U_FLASH)
                type = "sketch";
            else // U_SPIFFS
                type = "filesystem";

            // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
            LOG_LN("Start updating " << type);
        })
        .onEnd([]() {
            LOG_LN("\nEnd");
        })
        .onProgress([](unsigned int progress, unsigned int total) {
            LOG("Progress: " << (progress / (total / 100)) << "\r");
        })
        .onError([](ota_error_t error) {
            LOG("Error[" << error << "]: ");
            if (error == OTA_AUTH_ERROR) LOG_LN("Auth Failed");
            else if (error == OTA_BEGIN_ERROR) LOG_LN("Begin Failed");
            else if (error == OTA_CONNECT_ERROR) LOG_LN("Connect Failed");
            else if (error == OTA_RECEIVE_ERROR) LOG_LN("Receive Failed");
            else if (error == OTA_END_ERROR) LOG_LN("End Failed");
        });

    ArduinoOTA.begin();
    // do some checks here
    return true;
}

void OTA::handle() {
    ArduinoOTA.handle();
}
