#include "BleCharacteristicsHelper.h"

#include "Misc/Logger.h"

#include <Arduino.h>
#include <BLE2902.h>
#include <BLE2904.h>

#include <tuple>

static std::array<std::tuple<const char*, uint32_t, uint16_t>, index(ble::CharacteristicTypes::CHARACTERISTICS_COUNT)> propertiesArray = {
    std::make_tuple("00000002-0000-1000-8000-00805f9b34fb", BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY, 0x2902 ),  // battery level
    std::make_tuple("00000003-0000-1000-8000-00805f9b34fb", BLECharacteristic::PROPERTY_READ, 0 ),  // BT mac
    std::make_tuple("00000004-0000-1000-8000-00805f9b34fb", BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY, 0x2902 ),  // WIFI status
    std::make_tuple("00000005-0000-1000-8000-00805f9b34fb", BLECharacteristic::PROPERTY_WRITE, 0 ),  // WIFI creds
    std::make_tuple("00000006-0000-1000-8000-00805f9b34fb", BLECharacteristic::PROPERTY_WRITE, 0 ),  // notification
    std::make_tuple("00000007-0000-1000-8000-00805f9b34fb", BLECharacteristic::PROPERTY_WRITE, 0 ),  // time
};

namespace ble {
    CharacteristicCallbacks::CharacteristicCallbacks(const OnWriteFunc& write, const OnReadFunc& read, const OnNotifyFunc& notify)
        : mWriteFunc(write)
        , mReadFunc(read)
        , mNotifyFunc(notify)
    {}

    CharacteristicCallbacks::operator bool() {
        return mWriteFunc || mReadFunc || mNotifyFunc;
    }

    void CharacteristicCallbacks::onWrite(BLECharacteristic *pCharacteristic) {
        LOG_LN("characteristic write requested");
        if (mWriteFunc) {
            mWriteFunc(pCharacteristic->getValue());
        }
    }

    void CharacteristicCallbacks::onRead(BLECharacteristic* pCharacteristic) {
        LOG_LN("characteristic read requested");
        if (mReadFunc) {
            std::string data = "";
            mReadFunc(data);
            pCharacteristic->setValue(data);
            pCharacteristic->notify();
        }
    }

    void CharacteristicCallbacks::onNotify(BLECharacteristic* pCharacteristic) {
        LOG_LN("characteristic notify requested");
        if (mNotifyFunc) {
            mNotifyFunc();
        }
    }

    CharacteristicsBuilder::CharacteristicsBuilder(const CharacteristicCallbacksArray& callbacks) {
        for (unsigned int i = 0; i < index(CharacteristicTypes::CHARACTERISTICS_COUNT); i++) {
            //const auto& [uuid, flags, descriptor] = propertiesArray[i];
            const auto&  uuid = std::get<0>(propertiesArray[i]);
            const auto&  flags = std::get<1>(propertiesArray[i]);
            const auto&  descriptor = std::get<2>(propertiesArray[i]);

            mCharacteristics[i].mCallbacks = callbacks[i];
            mCharacteristics[i].mUUID = uuid;
            mCharacteristics[i].mProperties = flags;

            switch (descriptor) {
            case 0x2902:
                mCharacteristics[i].mDescriptor = new BLE2902();
                break;
            case 0x2904:
                mCharacteristics[i].mDescriptor = new BLE2904();
                break;
            default:
                break;
            }
        }
    }

    CharacteristicConfigsArray CharacteristicsBuilder::getCharacteristics() {
        return mCharacteristics;
    }
}  // ble
