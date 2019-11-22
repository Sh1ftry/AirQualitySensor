#ifndef AIR_QUALITY_SENSOR_H
#define AIR_QUALITY_SENSOR_H
#include <ArduinoLog.h>
#include <SoftwareSerial.h>
#include <PMS.h>

namespace Sensors
{
    class AirQuality
    {
        public:
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
            AirQuality(const int rx, const int tx) : softwareSerial(rx, tx), pms(softwareSerial) {}
            void init()
            {
                Log.notice(F("Initializing sensor"));
                softwareSerial.begin(9600);
            }

            Sensors::AirQuality::Measurement read()
            {
                if(pms.readUntil(reading))
                {
                    return Sensors::AirQuality::Measurement(true, reading.PM_SP_UG_1_0, reading.PM_SP_UG_2_5, reading.PM_SP_UG_10_0);
                }
                else
                {
                    return Sensors::AirQuality::Measurement(false, 0, 0, 0);
                }
            }    

        private:
            SoftwareSerial softwareSerial;
            PMS pms;
            PMS::DATA reading;
    };
}

#endif /* AIR_QUALITY_SENSOR_H */