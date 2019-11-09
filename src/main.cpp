#include <Arduino.h>
#include <ArduinoLog.h>
#include <SoftwareSerial.h>
#include <RF24.h>
#include <SPI.h>
#include "sensors/AirQuality.h"
#include "network/Wireless.h"
#include "network/MQTTClient.h"
#include "sensors/TemperatureAndHumidity.h"

const uint8_t SW_RX=12, SW_TX=13, TH_PIN=14;
const uint16_t BAUD_RATE=9600;

const char* MQTT_HOST = "farmer.cloudmqtt.com";
const uint16_t MQTT_PORT = 15304;
const char* MQTT_TOPIC = "sensors/air_quality_sensor";
const char* MQTT_TEMP_TOPIC = "sensors/temperature";
const char* MQTT_HUM_TOPIC = "sensors/humidity";

Network::Wireless wifi;
//Network::MQTTClient mqttClient(wifi);

//Sensors::AirQuality aqSensor(SW_RX, SW_TX);
//Sensors::TemperatureAndHumidity thSensor(TH_PIN);

RF24 radio(5, 6);

void setup()
{
  Serial.begin(BAUD_RATE);
  SPI.begin();

  Log.begin(LOG_LEVEL_VERBOSE, &Serial);
  Log.setSuffix([](Print* _logOutput){_logOutput->print('\n');});
  
  wifi.connect(WIFI_SSID, WIFI_PASSWORD, 30, 1000);
  //mqttClient.connect(MQTT_HOST, MQTT_PORT, MQTT_USER, MQTT_PASSWORD, 10, 1000);

  //thSensor.init();
  radio.begin();
  radio.setPALevel(RF24_PA_LOW);
  byte address[] = "radio";
  radio.openReadingPipe(1, address);
  radio.startListening();
  //aqSensor.init();
}

void loop()
{
  delay(5000);
  Log.trace(F("Checking radio"));
  if(radio.available())
  {
    Log.verbose(F("Radio available"));
    uint8_t data[] = "654";
    while(radio.available())
    {
      radio.read(data, sizeof(data));
    }
    Log.verbose("%s", data);
  }
  //auto thMeasurement = thSensor.read();
  //auto aqMeasurement = aqSensor.read(); 
  //if(aqMeasurement.pm01 != -1)
  //  mqttClient.publish(MQTT_TOPIC, aqMeasurement.toJson().c_str(), true);
  //mqttClient.publish(MQTT_HUM_TOPIC, thMeasurement.humidity, true);
  //mqttClient.publish(MQTT_TEMP_TOPIC, thMeasurement.temperature, true);
}