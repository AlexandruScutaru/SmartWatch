#pragma once

#include <Arduino.h>

#include <functional>
#include <memory>


class BLEServer;
class BLEService;
class BLECharacteristic;
class BLEAdvertising;

struct Callbacks {
    using OnWriteFunc = std::function<void(const std::string&)>;
    using OnReadFunc = std::function<void()>;
    using OnNotifyFunc = std::function<void()>;

    OnWriteFunc write{ nullptr };
    OnReadFunc read{ nullptr };
    OnNotifyFunc notify{ nullptr };
};

class BLE {
public:
    BLE(const std::string& deviceName, const Callbacks& callbacks);
    ~BLE();

    void sendData(const std::string& data);

private:
    BLEServer* mServer{ nullptr };
    BLEService* mService{ nullptr };
    BLECharacteristic* mCharacteristic{ nullptr };
    BLEAdvertising* mAdvertising{ nullptr };

};

using BLEPtr = std::shared_ptr<BLE>;
