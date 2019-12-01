#include <Arduino.h>
#include <PMS.h>
#include <SoftwareSerial.h>
#include "Sensor.h"

#define MEASUREMENT_BUFFER_SIZE 32
#define WAKE_UP_TIME_DELAY_MS 30000

class AirQualitySensor: public WeatherStation::Sensor
{
    public:
        AirQualitySensor(uint8_t rx, uint8_t tx)
            : softwareSerial(rx, tx), pms(softwareSerial) {}

        bool setup() override
        {
            softwareSerial.begin(pms.BAUD_RATE);
            pms.passiveMode();
            return true;
        }

        void wake() override
        {
            pms.wakeUp();
            //sleep WAKE_UP_TIME_DELAY_MS
            delay(WAKE_UP_TIME_DELAY_MS);
        }
        
        void sleep() override
        {
            pms.sleep();
        }
        
        const char* read() override
        {
            buffer[0] = '\0';
            
            pms.requestRead();
            if(pms.readUntil(data))
            {
                snprintf(buffer, MEASUREMENT_BUFFER_SIZE, "%d,%d,%d", 
                    data.PM_AE_UG_1_0, data.PM_AE_UG_2_5, data.PM_AE_UG_10_0);
            }

            return buffer;
        }
    
    private:
        SoftwareSerial softwareSerial;
        PMS pms;
        PMS::DATA data;
        char buffer[MEASUREMENT_BUFFER_SIZE];
};