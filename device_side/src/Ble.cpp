#include "Ble.h"

#include "Logger.h"

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

// See the following for generating UUIDs:
// https://www.uuidgenerator.net/

#define SERVICE_UUID        "6e400001-b5a3-f393-e0a9-e50e24dcca9e"
#define CHARACTERISTIC_UUID "6e400003-b5a3-f393-e0a9-e50e24dcca9e"

//not sure what the rest of the methods do
class BleCallbacks : public BLECharacteristicCallbacks {
public:
    BleCallbacks(const Callbacks& callbacks) 
        : mCallbacks(callbacks)
    {}

private:
    void onWrite(BLECharacteristic *pCharacteristic) {
        if (mCallbacks.write) {
            mCallbacks.write(pCharacteristic->getValue());
        }
    }

    void onNotify(BLECharacteristic* pCharacteristic) {
        if (mCallbacks.notify) {
            mCallbacks.notify();
        }
    }

    void onRead(BLECharacteristic* pCharacteristic) {
        if (mCallbacks.read) {
            mCallbacks.read();
        }
    }

    Callbacks mCallbacks;
};


BLE::BLE(const std::string& deviceName, const Callbacks& callbacks) {
    BLEDevice::init(deviceName);
    mServer = BLEDevice::createServer();
    mService = mServer->createService(SERVICE_UUID);
    mCharacteristic = mService->createCharacteristic(
        CHARACTERISTIC_UUID, 
        BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE | BLECharacteristic::PROPERTY_NOTIFY
    );

    mCharacteristic->setCallbacks(new BleCallbacks(callbacks));
    mCharacteristic->setValue("I'm a SmartWatch");
    mService->start();

    // BLEAdvertising *pAdvertising = pServer->getAdvertising();    // this still is working for backward compatibility
    mAdvertising = BLEDevice::getAdvertising();
    mAdvertising->addServiceUUID(SERVICE_UUID);
    mAdvertising->setScanResponse(true);
    mAdvertising->setMinPreferred(0x06);    // functions that help with iPhone connections issue
    mAdvertising->setMinPreferred(0x12);
    BLEDevice::startAdvertising();

    LOG_LN("BLE init completed");
}

BLE::~BLE() {
    //not sure exactly if I have ownership of these
    if (mServer) {
        delete mServer;
        mServer = nullptr;
    }
    if (mService) {
        delete mService;
        mService = nullptr;
    }
    if (mCharacteristic) {
        delete mCharacteristic;
        mCharacteristic = nullptr;
    }
    if (mAdvertising) {
        delete mAdvertising;
        mAdvertising = nullptr;
    }
}

void BLE::sendData(const std::string& data) {
    if (mCharacteristic) {
        mCharacteristic->setValue(data.c_str());
        mCharacteristic->notify();
    }
}