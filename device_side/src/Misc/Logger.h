#pragma once

#include <sstream>
#include <functional>
#include <memory>


namespace web {
    class WebSocket;
}

// kinda bad way to create a logger, but this is not vital in this project,
// I just need a way to get some info either on serial or via websockets to a web page
namespace logging {
    void initSerialLogger();
    std::shared_ptr<web::WebSocket> initWebSocketLogger();

    class Log {
    public:
        static Log& Instance();

        void log(const std::string& str);

    private:
        Log() = default;
        Log(const Log&) = delete;
        Log(Log&&) = delete;
        Log& operator= (const Log&) = delete;
        Log& operator= (Log&&) = delete;

        using LoggingStrategy = std::function<void(const std::string&)>;
        void setLoggingStrategy(const LoggingStrategy& loggingStrat);
        LoggingStrategy mLogFunc{ nullptr };

        friend void initSerialLogger();
        friend std::shared_ptr<web::WebSocket> initWebSocketLogger();

    };
}

#if defined(SERIAL_LOGGER) || defined(WS_LOGGER)
    #define LOG(message) do { std::stringstream ss; ss << message; logging::Log::Instance().log(ss.str()); } while(0)
    #define LOG_LN(message) do { std::stringstream ss; ss << message << "\n"; logging::Log::Instance().log(ss.str()); } while(0)
#else
    #define LOG(message)
    #define LOG_LN(message)
#endif
