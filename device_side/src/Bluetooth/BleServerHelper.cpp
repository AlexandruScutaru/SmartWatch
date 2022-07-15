#include "BleServerHelper.h"

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

#include "Misc/Logger.h"

#define SERVICE_UUID    "00000001-0000-1000-8000-00805f9b34fb"


bool deviceConnected = false;
bool oldDeviceConnected = false;

namespace ble {
    ServerCallbacks::ServerCallbacks(const ServerCallbackFunc& onConnect, const ServerCallbackFunc& onDisconnect)
        : mOnConnectFunc(onConnect)
        , mOnDisconnectFunc(onDisconnect)
    {}

    void ServerCallbacks::onConnect(BLEServer* pServer) {
        if (mOnConnectFunc) {
            mOnConnectFunc(pServer);
        }
    }
    void ServerCallbacks::onDisconnect(BLEServer* pServer) {
        if (mOnDisconnectFunc) {
            mOnDisconnectFunc(pServer);
        }
    }


    Server::Server(const std::string& name, const CharacteristicConfigsArray& configs) {
        mServerCallbacks = ServerCallbacks(
            [this](BLEServer* server) {
                onConnect(server);
            },
            [this](BLEServer* server) {
                onDisconnect(server);
            }
        );

        BLEDevice::init(name);
        mServer = BLEDevice::createServer();
        mServer->setCallbacks(&mServerCallbacks);

        mService = mServer->createService(SERVICE_UUID);

        for (unsigned int i = 0; i < index(CharacteristicTypes::CHARACTERISTICS_COUNT); i++) {
            mCharacteristics[i].mCharacteristic = mService->createCharacteristic(configs[i].mUUID, configs[i].mProperties);
            mCharacteristics[i].mCallbacks =  configs[i].mCallbacks;
            mCharacteristics[i].mCharacteristic->setValue("");

            if (mCharacteristics[i].mCallbacks) {
                mCharacteristics[i].mCharacteristic->setCallbacks(&mCharacteristics[i].mCallbacks);
            }

            if (mCharacteristics[i].mDescriptor) {
                mCharacteristics[i].mCharacteristic->addDescriptor(mCharacteristics[i].mDescriptor);
            }
        }

        mService->start();

        mAdvertising = BLEDevice::getAdvertising();
        mAdvertising->addServiceUUID(SERVICE_UUID);
        mAdvertising->setScanResponse(true);
        mAdvertising->setMinPreferred(0x06);    // functions that help with iPhone connections issue
        mAdvertising->setMinPreferred(0x12);
        BLEDevice::startAdvertising();

        LOG_LN("BLE init completed");
    }

    Server::~Server() {
        delete mAdvertising;
        mAdvertising = nullptr;

        for (unsigned int i = 0; i < index(CharacteristicTypes::CHARACTERISTICS_COUNT); i++) {
            delete mCharacteristics[i].mDescriptor;
            mCharacteristics[i].mDescriptor = nullptr;

            delete mCharacteristics[i].mCharacteristic;
            mCharacteristics[i].mCharacteristic = nullptr;
        }

        delete mService;
        mService = nullptr;

        delete mServer;
        mServer = nullptr;
    }

    void Server::sendData(const std::string& data) {
        if (const auto& characteristic = mCharacteristics[0].mCharacteristic) {
            characteristic->setValue(data);
            characteristic->notify();
        }
    }

    void Server::onConnect(BLEServer* server) {
        LOG_LN("device connected");
    }

    void Server::onDisconnect(BLEServer* server) {
        LOG_LN("device disconnected");
        delay(500); // give the bluetooth stack the chance to get things ready
                    // is this really necessary??
        LOG_LN("start advertising");
        server->startAdvertising();
    }
}  // ble
