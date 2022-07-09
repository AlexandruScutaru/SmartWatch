#include "WebSocket.h"
#include "Logger.h"


namespace web {
    namespace {
        void onWebSocketEvent(WebSocketsServer& webSocket, const WebSocketCallbacks& callbacks, uint8_t clientId, WStype_t eventType, uint8_t* data, size_t length) {
            switch (eventType)
            {
                case WStype_CONNECTED:
                {
                    IPAddress ip = webSocket.remoteIP(clientId);
                    LOG_LN("Client " << clientId << " connected! IP: " << ip[0] << "." << ip[1] << "." << ip[2] << "." << ip[3] << " url: " << data);
                    if (callbacks.mOnConnectedFunc) {
                        callbacks.mOnConnectedFunc(clientId);
                    }
                }
                case WStype_DISCONNECTED:
                    LOG_LN("Client " << clientId << " disconnected!");
                    if (callbacks.mOnDisconnectedFunc) {
                        callbacks.mOnDisconnectedFunc(clientId);
                    }
                    break;
                case WStype_TEXT:
                    LOG_LN("Client " << clientId << " sent some text data");
                    if (callbacks.mOnTextReceiveFunc) {
                        callbacks.mOnTextReceiveFunc(clientId, data, length);
                    }
                    break;
                case WStype_BIN:
                    LOG_LN("Client " << clientId << " sent some binary data");
                    if (callbacks.mOnBinReceiveFunc) {
                        callbacks.mOnBinReceiveFunc(clientId, data, length);
                    }
                    break;
                case WStype_ERROR:
                case WStype_FRAGMENT_TEXT_START:
                case WStype_FRAGMENT_BIN_START:
                case WStype_FRAGMENT:
                case WStype_FRAGMENT_FIN:
                default:
                    LOG_LN("Client " << clientId << " triggered other type of WStype_t event");
                    break;
            }
        }
    }

    WebSocket::WebSocket(uint16_t port, const WebSocketCallbacks& callbacks)
        : mWebSocket(WebSocketsServer(port))
        , mCallbacks(callbacks)
    {
        mWebSocket.begin();
        mWebSocket.onEvent( [&webSocket = mWebSocket, &callbacks = mCallbacks](uint8_t clientId, WStype_t eventType, uint8_t* data, size_t length) {
            onWebSocketEvent(webSocket, callbacks, clientId, eventType, data, length);
        });
    }

    bool WebSocket::broadcast(const std::string& message) {
        return mWebSocket.broadcastTXT(message.c_str());
    }

    bool WebSocket::broadcast(uint8_t* data, size_t length) {
        return mWebSocket.broadcastBIN(data, length);
    }

    void WebSocket::update() {
        mWebSocket.loop();
    }
}
