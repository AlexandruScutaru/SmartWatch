#include "Ble.h"

#include "Logger.h"

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

// See the following for generating UUIDs:
// https://www.uuidgenerator.net/

#define SERVICE_UUID                      "00000001-0000-1000-8000-00805f9b34fb"
// read characteristics
#define BATTERY_CHARACTERISTIC_UUID       "00000002-0000-1000-8000-00805f9b34fb"
#define BT_MAC_CHARACTERISTIC_UUID        "00000003-0000-1000-8000-00805f9b34fb"
#define WIFI_STATUS_CHARACTERISTIC_UUID   "00000004-0000-1000-8000-00805f9b34fb"
#define WIFI_SSID_CHARACTERISTIC_UUID     "00000005-0000-1000-8000-00805f9b34fb"
// write characteristics
#define NOTIFICATION_CHARACTERISTIC_UUID  "00000006-0000-1000-8000-00805f9b34fb"


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

    BLECharacteristic* characteristic = nullptr;
    //todo: do these in a better way, but for now they are just for testing
    //battery level
    characteristic = mService->createCharacteristic(
        BATTERY_CHARACTERISTIC_UUID,
        BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY
    );
    characteristic->setValue("78");
    mCharacteristics.push_back(characteristic);

    //device mac
    characteristic = mService->createCharacteristic(
        BT_MAC_CHARACTERISTIC_UUID,
        BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY
    );
    characteristic->setValue("00:00:du:mm:y0:00:00:00");
    mCharacteristics.push_back(characteristic);

    //wifi status
    characteristic = mService->createCharacteristic(
        WIFI_STATUS_CHARACTERISTIC_UUID,
        BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY
    );
    characteristic->setValue("true");
    mCharacteristics.push_back(characteristic);

    //wifi ssid
    characteristic = mService->createCharacteristic(
        WIFI_SSID_CHARACTERISTIC_UUID,
        BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY
    );
    characteristic->setValue("Wifi_Name");
    mCharacteristics.push_back(characteristic);

    //phone notification
    characteristic = mService->createCharacteristic(
        NOTIFICATION_CHARACTERISTIC_UUID,
        BLECharacteristic::PROPERTY_WRITE
    );
    characteristic->setCallbacks(new BleCallbacks(callbacks));
    mCharacteristics.push_back(characteristic);

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
    if (mServer) {
        delete mServer;
        mServer = nullptr;
    }
    if (mService) {
        delete mService;
        mService = nullptr;
    }
    for (size_t i = 0; i < mCharacteristics.size(); i++) {
        delete mCharacteristics[i];
    }
    mCharacteristics.clear();
    if (mAdvertising) {
        delete mAdvertising;
        mAdvertising = nullptr;
    }
}

void BLE::sendData(const std::string& data) {
    if (const auto& characteristic = mCharacteristics[0]) {
        characteristic->setValue(data);
        characteristic->notify();
    }
}