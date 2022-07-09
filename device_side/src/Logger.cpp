#include "Logger.h"
#include "WebSocket.h"

#include <Arduino.h>


namespace logging {
    void initSerialLogger() {
        Log::Instance().setLoggingStrategy([](const std::string& message){
            Serial.print(message.c_str());
        });
    }

    std::shared_ptr<web::WebSocket> initWebSocketLogger() {
        auto ws = std::make_shared<web::WebSocket>(80, web::WebSocketCallbacks());

        Log::Instance().setLoggingStrategy([weak_ws = std::weak_ptr<web::WebSocket>(ws)](const std::string& message) {
            Serial.print(message.c_str());
            if (auto ws = weak_ws.lock()) {
                ws->broadcast(message);
            }
        });

        return ws;
    }

    Log& Log::Instance() {
        static Log log;
        return log;
    }

    void Log::log(const std::string& str) {
        if (mLogFunc) {
            mLogFunc(str);
        }
    }

    void Log::setLoggingStrategy(const LoggingStrategy& loggingStrat) {
        mLogFunc = loggingStrat;
    }
}
