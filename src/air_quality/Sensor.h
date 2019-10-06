#ifndef AIR_QUALITY_SENSOR_H
#define AIR_QUALITY_SENSOR_H
#include <PMserial.h>
#include <ArduinoLog.h>
#include "Measurement.h"

namespace AirQuality
{
    class Sensor
    {
        public:
            Sensor(const int rx, const int tx) : pms(PMS5003, rx, tx) {}
            void init()
            {
                Log.notice(F("Initializing sensor"));
                pms.init();
            }

            Measurement read()
            {
                pms.read();
                if(pms)
                {
                    return Measurement(true, pms.pm01, pms.pm25, pms.pm10);
                }
                else
                {
                    return Measurement(false, 0, 0, 0);
                }
            }    

        private:
            SerialPM pms;
    };
}

#endif /* AIR_QUALITY_SENSOR_H */