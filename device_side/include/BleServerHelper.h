#pragma once

#include "BleCharacteristicsHelper.h"

#include <memory>

#include <Arduino.h>
#include <BLEServer.h>


namespace ble {
    class ServerCallbacks : public BLEServerCallbacks {
    public:
        using ServerCallbackFunc = std::function<void(BLEServer*)>;
        ServerCallbacks(const ServerCallbackFunc& onConnect = nullptr, const ServerCallbackFunc& onDisconnect = nullptr);

    private:
        void onConnect(BLEServer* pServer) override;
        void onDisconnect(BLEServer* pServer) override;

        ServerCallbackFunc mOnConnectFunc{ nullptr };
        ServerCallbackFunc mOnDisconnectFunc{ nullptr };
    };

    class Server {
    public:
        Server(const std::string& name, const CharacteristicConfigsArray& configs);
        ~Server();

        void sendData(const std::string& data);

    private:
        void onConnect(BLEServer* server);
        void onDisconnect(BLEServer* server);

        BLEServer* mServer{ nullptr };
        BLEService* mService{ nullptr };
        CharacteristicConfigsArray mCharacteristics;
        BLEAdvertising* mAdvertising{ nullptr };
        ServerCallbacks mServerCallbacks;

    };

    using ServerPtr = std::shared_ptr<Server>;
}  // ble
