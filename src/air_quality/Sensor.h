#ifndef AIR_QUALITY_SENSOR_H
#define AIR_QUALITY_SENSOR_H
#include <ArduinoLog.h>
#include <SoftwareSerial.h>
#include <PMS.h>
#include "Measurement.h"

namespace AirQuality
{
    class Sensor
    {
        public:
            Sensor(const int rx, const int tx) : softwareSerial(rx, tx), pms(softwareSerial) {}
            void init()
            {
                Log.notice(F("Initializing sensor"));
                softwareSerial.begin(9600);
            }

            Measurement read()
            {
                if(pms.readUntil(reading))
                {
                    return Measurement(true, reading.PM_SP_UG_1_0, reading.PM_SP_UG_2_5, reading.PM_SP_UG_10_0);
                }
                else
                {
                    return Measurement(false, -1, -1, -1);
                }
            }    

        private:
            SoftwareSerial softwareSerial;
            PMS pms;
            PMS::DATA reading;
    };
}

#endif /* AIR_QUALITY_SENSOR_H */