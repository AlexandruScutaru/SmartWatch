#include "BatteryUtils.h"

#include <Arduino.h>

#define PIN_BATTERY_LEVEL    33
#define PERCENTAGE_BIAS      0.2
#define MAX_ANALOG_READ      4095.0
#define REFERENCE_VOLTAGE    3.3
#define MAX_CHARGE           4.2
#define MIN_ACCPETED_CHARGE  3.7


namespace BatteryUtils {

    namespace {
        struct VoltagePercentagePair{
            double voltage;
            uint8_t percentage;
        };

        double averageVoltage = 0.0;
        double voltages[100] = {0};
        size_t index = 0U;
        uint8_t percentage = 0U;

        //lipo charge levels
        VoltagePercentagePair voltageRanges[] = {
            { 4.20, 100 }, //avoid full charge
            { 4.15,  95 }, //charge at most to this point
            { 4.11,  90 },
            { 4.08,  85 },
            { 4.02,  80 },
            { 3.98,  75 },
            { 3.95,  70 },
            { 3.91,  65 },
            { 3.87,  60 },
            { 3.85,  55 },
            { 3.84,  50 },
            { 3.82,  45 },
            { 3.80,  40 },
            { 3.79,  35 },
            { 3.77,  30 },
            { 3.75,  25 },
            { 3.73,  20 }, //recharge now
            { 3.71,  15 }, //bad
            { 3.69,  10 }, //very bad
            { 3.61,   5 }, //critical
            { 3.27,   0 }, //dead
        };


        byte getAssociatedPercentage() {
            size_t nb = sizeof(voltageRanges) / sizeof(voltageRanges[0]);
            size_t index = 0;
            for (index = 0; index < nb; index++) {
                if (averageVoltage > voltageRanges[index].voltage)
                    break;
            }

            if(index == nb)
                return 0;

            if(index)
                index--;

            return min((int)((averageVoltage - voltageRanges[index+1].voltage) / (voltageRanges[index].voltage - voltageRanges[index+1].voltage) * 
                            (voltageRanges[index].percentage - voltageRanges[index+1].percentage) + voltageRanges[index+1].percentage), 100);
        }
    }

    uint8_t GetBatteryLevel() {
        voltages[index++] = 2 * (REFERENCE_VOLTAGE * analogRead(PIN_BATTERY_LEVEL) / MAX_ANALOG_READ) + PERCENTAGE_BIAS;
        percentage = min((int)((voltages[0] - MIN_ACCPETED_CHARGE) / (MAX_CHARGE - MIN_ACCPETED_CHARGE) * (100 - 10) + 10), 100);

        if(100 == index) {
            double sum = 0.0;
            for(size_t i = 0; i < 100; i++)
                sum += voltages[i];

            averageVoltage = sum / 100.0;
            index = 0;
            percentage = getAssociatedPercentage();
        }

        return percentage;
    }

    double GetBatteryVoltage() {
        return averageVoltage;
    }

}
