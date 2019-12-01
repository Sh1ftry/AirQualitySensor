#ifndef WS_DEVICE_H
#define WS_DEVICE_H

#include "Measurement.h"

namespace WeatherStation
{
    class Sensor
    {
        public:
            virtual bool setup() = 0;
            virtual void sleep() = 0;
            virtual const char* read() = 0;
            virtual void wake() = 0;
    };
}

#endif