#include <Arduino.h>
#include <ArduinoLog.h>
#include <SoftwareSerial.h>
#include <RF24.h>
#include "sensors/AirQuality.h"
#include "network/Wireless.h"
#include "network/MQTTClient.h"
#include "sensors/TemperatureAndHumidity.h"

const uint8_t SW_RX=12, SW_TX=13;
const uint16_t BAUD_RATE=9600;

#ifdef MQTT_ENABLED
const char* MQTT_HOST = "farmer.cloudmqtt.com";
const uint16_t MQTT_PORT = 15304;
const char* MQTT_TOPIC = "sensors/air_quality_sensor";
const char* MQTT_TEMP_TOPIC = "sensors/temperature";
const char* MQTT_HUM_TOPIC = "sensors/humidity";
Network::Wireless wifi;
Network::MQTTClient mqttClient(wifi);
#endif

const uint64_t address = 0xABCDABCD71LL;
RF24 radio(5, 4);

void setup()
{
  Serial.begin(BAUD_RATE);

  Log.begin(LOG_LEVEL_VERBOSE, &Serial);
  Log.setSuffix([](Print* _logOutput){_logOutput->print('\n');});
  
  #ifdef MQTT_ENABLED
  wifi.connect(WIFI_SSID, WIFI_PASSWORD, 30, 1000);
  mqttClient.connect(MQTT_HOST, MQTT_PORT, MQTT_USER, MQTT_PASSWORD, 10, 1000);
  #endif
  
  Log.trace(F("Initializing radio"));
  if(radio.begin()) {
    Log.trace(F("Setting radio configuration"));
    radio.setPALevel(RF24_PA_MIN);
    radio.setDataRate(RF24_250KBPS);
    Log.trace(F("Opening reading pipe"));
    radio.openReadingPipe(1, address);
    Log.trace(F("Starting listening"));
    radio.startListening();
    radio.printDetails();
  } else {
    Log.error(F("Initialization failed"));
    delay(1000);
    ESP.reset();
  }
}

void loop()
{
  if(radio.available())
  {
    Log.verbose(F("Radio available"));
    char data[32];
    radio.read(data, sizeof(data));
    data[31] = '\0'; 
    Log.verbose("%s", data);
  }
}