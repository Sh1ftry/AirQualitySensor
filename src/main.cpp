#include <Arduino.h>
#include <SoftwareSerial.h>
#include <ArduinoLog.h>
#include "sensor/AirQualitySensor.h"

const uint8_t SENSOR_RX=12, SENSOR_TX=13, LED=14;
const uint16_t BAUD_RATE=9600;
AirQualitySensor sensor(SENSOR_RX, SENSOR_TX);

void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(BAUD_RATE);
  Log.begin(LOG_LEVEL_VERBOSE, &Serial);
  Log.setSuffix([](Print* _logOutput){_logOutput->print('\n');});
  Log.notice(F("Initializing sensor"));
  sensor.init();
}

int current = HIGH;
void loop() {
  Measurement measurement = sensor.read();

  if(measurement.success)
  {
    Log.notice("Measurement ready");
  }
  else
  {
    Log.warning("Could not get readings from sensor");
  }
  
  Log.trace("Tick");
  delay(1000);
  digitalWrite(LED, current);
  if(current == HIGH) current = LOW;
  else current = HIGH;
}