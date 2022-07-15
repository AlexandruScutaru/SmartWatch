#pragma once

#include <WebSocketsServer.h>

#include <functional>


namespace web {
    struct WebSocketCallbacks {
        using OnConnected = std::function<void(uint8_t)>;
        using OnDisconnected = std::function<void(uint8_t)>;
        using OnTextReceive = std::function<void(uint8_t, uint8_t*, size_t)>;
        using OnBinReceive = std::function<void(uint8_t, uint8_t*, size_t)>;

        OnConnected mOnConnectedFunc{ nullptr };
        OnDisconnected mOnDisconnectedFunc{ nullptr };
        OnTextReceive mOnTextReceiveFunc{ nullptr };
        OnBinReceive mOnBinReceiveFunc{ nullptr };
    };

    class WebSocket {
    public:
        WebSocket(uint16_t port, const WebSocketCallbacks& callbacks);

        // wrapped only the broadcast for now
        bool broadcast(const std::string& message);
        bool broadcast(uint8_t* data, size_t length);
        void update();

    private:
        WebSocketsServer mWebSocket;
        WebSocketCallbacks mCallbacks;

    };
}
