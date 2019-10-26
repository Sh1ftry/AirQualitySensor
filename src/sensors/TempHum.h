#ifndef TEMP_HUM_SENSOR_H
#define TEMP_HUM_SENSOR_H

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <ArduinoLog.h>

namespace Sensors {
    class TempHum {
        private:
            DHT dht;
        public:
            class Measurement
            {
                public:
                    Measurement(float t, float h): temperature(t), humidity(h) {}
                    const float temperature;
                    const float humidity;
            };
            
            TempHum(uint8_t pin): dht(pin, DHT22) {}
            
            void begin()
            {
                Log.notice(F("Initializing DHT sensor"));
                dht.begin();
            }

            Sensors::TempHum::Measurement read()
            {
                Log.notice(F("Reading DHT sensor"));
                float h = dht.readHumidity();
                float t = dht.readTemperature();
                if (isnan(h) || isnan(t)) {
                    return Sensors::TempHum::Measurement(-1., -1.);
                }
                return Sensors::TempHum::Measurement(t, h);
            }
    };
}
#endif /* TEMP_HUM_SENSOR_H */