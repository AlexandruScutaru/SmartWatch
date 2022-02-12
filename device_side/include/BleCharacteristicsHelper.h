#pragma once

#include <array>
#include <functional>
#include <string>

#include <BLECharacteristic.h>
#include <BLE2902.h>

class BLECharacteristic;
class BLEDescriptor;

namespace ble {
    enum class CharacteristicTypes;
    struct CharacteristicCallbacks;
    struct CharacteristicConfig;
}

constexpr unsigned int index(ble::CharacteristicTypes type) {
    return static_cast<unsigned int>(type);
}

namespace ble {
    enum class CharacteristicTypes {
        BATTERY_PERCENTAGE = 0,
        BT_MAC,
        WIFI_STATUS,
        WIFI_CREDS,
        NOTIFICATION,
        TIME,
        CHARACTERISTICS_COUNT,
    };

    using CharacteristicCallbacksArray = std::array<CharacteristicCallbacks, index(CharacteristicTypes::CHARACTERISTICS_COUNT)>;
    using CharacteristicConfigsArray = std::array<CharacteristicConfig, index(CharacteristicTypes::CHARACTERISTICS_COUNT)>;

    class CharacteristicCallbacks : public BLECharacteristicCallbacks {
    public:
        using OnWriteFunc = std::function<void(const std::string&)>;
        using OnReadFunc = std::function<void(std::string&)>;
        using OnNotifyFunc = std::function<void()>;

        CharacteristicCallbacks(const OnWriteFunc& write = nullptr,
                                const OnReadFunc& read = nullptr,
                                const OnNotifyFunc& notify = nullptr);

        operator bool();

        void onWrite(BLECharacteristic *pCharacteristic) override;
        void onRead(BLECharacteristic* pCharacteristic) override;
        void onNotify(BLECharacteristic* pCharacteristic) override;

        OnWriteFunc mWriteFunc{ nullptr };
        OnReadFunc mReadFunc{ nullptr };
        OnNotifyFunc mNotifyFunc{ nullptr };

    };

    struct CharacteristicConfig {
        BLECharacteristic* mCharacteristic{ nullptr };
        const char* mUUID{ nullptr };
        uint32_t mProperties{ 0 };
        CharacteristicCallbacks mCallbacks;
        BLEDescriptor* mDescriptor{ nullptr };
    };

    //not really a builder, but the name seems to give some pretentious meaning to it
    class CharacteristicsBuilder {
    public:
        CharacteristicsBuilder(const CharacteristicCallbacksArray& callbacks);

        CharacteristicConfigsArray getCharacteristics();

    private:
        CharacteristicConfigsArray mCharacteristics;

    };
}  // ble
