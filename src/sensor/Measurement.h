#include <Arduino.h>

class Measurement
{
    public:
    Measurement(bool success, uint16_t pm01, uint16_t pm25, uint16_t pm10) : 
        success(success), pm01(pm01), pm25(pm25), pm10(pm10) {}

    uint16_t pm01;
    uint16_t pm25;
    uint16_t pm10;
    bool success;

    String toString()
    {
        return "Measurement(PM1.0=" + String(pm01) + ",PM2.5=" + String(pm25) + ",PM10=" + String(pm10);
    }
};