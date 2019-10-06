#ifndef AIR_QUALITY_MEASUREMENT_H
#define AIR_QUALITY_MEASUREMENT_H
#include <Arduino.h>

namespace AirQuality
{
    class Measurement
    {
        public:
            Measurement(bool success, uint16_t pm01, uint16_t pm25, uint16_t pm10) : 
                success(success), pm01(pm01), pm25(pm25), pm10(pm10) {}

            bool success;
            uint16_t pm01;
            uint16_t pm25;
            uint16_t pm10;

            String toJson()
            {
                return "{\"pm01\":" + String(pm01) + ",\"pm25\":" + String(pm25) + ",\"pm10\":" + String(pm10) + "}";
            }
    };
}

#endif /* AIR_QUALITY_MEASUREMENT_H */