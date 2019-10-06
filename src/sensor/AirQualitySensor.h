#ifndef AIR_QUALITY_SENSOR_H
#define AIR_QUALITY_SENSOR_H
#include <PMserial.h>
#include "Measurement.h"

class AirQualitySensor
{
    public:
    AirQualitySensor(const int rx, const int tx) : pms(PMS5003, rx, tx) {}
    void init()
    {
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

#endif /* AIR_QUALITY_SENSOR_H */