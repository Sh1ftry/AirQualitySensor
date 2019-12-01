#include <Arduino.h>
#include <ArduinoLog.h>
#include <SoftwareSerial.h>
#include <RF24.h>
#include "sensors/AirQuality.h"
#include "AirQualitySensor/AitQualitySensor.h"
#include "Configuration.h"
#include "Sensor.h"

const uint8_t SW_RX=2, SW_TX=3;
const uint16_t BAUD_RATE=9600;

const uint64_t address = 0xABCDABCD71LL;
Sensors::AirQuality aqSensor(A0, A1);
RF24 radio(10, 9);

void setup()
{
  Serial.begin(BAUD_RATE);

  Log.begin(LOG_LEVEL_VERBOSE, &Serial);
  Log.setSuffix([](Print* _logOutput){_logOutput->print('\n');});
  
  aqSensor.init();

  Log.trace(F("Initializing radio"));
  if(radio.begin())
  {
    Log.trace(F("Setting radio configuration"));
    radio.setPALevel(RF24_PA_MIN);
    radio.setDataRate(RF24_250KBPS);
    radio.openWritingPipe(address);
    radio.stopListening();
    radio.printDetails();
  }
  else
  {
    Log.error(F("Initialization failed"));
  }
}

struct {
  uint8_t address;
  char payload[31];
} packet;

void loop()
{
  delay(5000);
  
  packet.address = 231;

  auto measurement = aqSensor.read();
  memset(packet.payload, 0, sizeof(packet.payload));
  sprintf(packet.payload, "%d,%d,%d", measurement.pm01, measurement.pm25, measurement.pm10);

  if(!radio.write(&packet, sizeof(packet)))
  {
    Log.warning(F("Ack not received"));
  }
}
