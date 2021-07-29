#include "BatteryUtils.h"

#include <Arduino.h>

#define PIN_BATTERY_LEVEL           33
#define PERCENTAGE_BIAS             0.2
#define MAX_ANALOG_READ             4095.0
#define REFERENCE_VOLTAGE           3.3
#define MAX_CHARGE                  4.2
#define MIN_ACCPETED_CHARGE         3.7
#define MAX_PERCENTAGE              100
#define MIN_ACCEPTED_PERCENTAGE     10
#define PERCENTAGE_RANGE_DIFFERENCE (MAX_PERCENTAGE - MIN_ACCEPTED_PERCENTAGE)
#define NB_READS_TO_AVERAGE         50


namespace BatteryUtils {

    namespace {
        struct VoltagePercentagePair{
            double voltage;
            uint8_t percentage;
        };

        double averageVoltage = 0.0;
        double voltages[NB_READS_TO_AVERAGE] = {0};
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
        //2* is used because max voltage of battery (4.2V) exceeds the analog read of 3.3v of the board
        //so the battery sensing wire is part of a voltage divider to be in the expected range [0, 3.3]
        //the PERCENTAGE_BIAS (0.2) is empirically deduced to get a closer voltage to a real meter reading
        voltages[index++] = 2 * (REFERENCE_VOLTAGE * analogRead(PIN_BATTERY_LEVEL) / MAX_ANALOG_READ) + PERCENTAGE_BIAS;
        //percentage = std::min((int)((voltages[0] - MIN_ACCPETED_CHARGE) / (MAX_CHARGE - MIN_ACCPETED_CHARGE) * ((int)PERCENTAGE_RANGE_DIFFERENCE) + MIN_ACCEPTED_PERCENTAGE), MAX_PERCENTAGE);

        if(index == NB_READS_TO_AVERAGE) {
            double sum = 0.0;
            for(size_t i = 0; i < NB_READS_TO_AVERAGE; i++)
                sum += voltages[i];

            averageVoltage = sum / float(NB_READS_TO_AVERAGE);
            index = 0;
            percentage = getAssociatedPercentage();
        }

        return percentage;
    }

    double GetBatteryVoltage() {
        return averageVoltage;
    }

}
