#include <Arduino.h>
#include <ArduinoLog.h>
#include <SoftwareSerial.h>
#include "air_quality/Sensor.h"
#include "network/Wireless.h"
#include "network/MQTTClient.h"
#include "sensors/TempHum.h"

#define DHTTYPE DHT22
#define DHTPIN 14

const uint8_t SW_RX=12, SW_TX=13, AM2320_PIN=14;
const uint16_t BAUD_RATE=9600;

const char* WIFI_SSID = "OnePlus 6T";
const char* WIFI_PASSWORD = "c9f814a0fb34";
const char* MQTT_HOST = "broker.hivemq.com";
const uint16_t MQTT_PORT = 1883;
const char* MQTT_TOPIC = "sensors/air_quality_sensor";
const char* MQTT_TEMP_TOPIC = "sensors/temperature";
const char* MQTT_HUM_TOPIC = "sensors/humidity";

//AirQuality::Sensor sensor(SW_RX, SW_TX);
Network::Wireless wifi;
Network::MQTTClient mqttClient(wifi);
Sensors::TempHum tempHumSensor(AM2320_PIN);

void setup()
{
  Serial.begin(BAUD_RATE);

  Log.begin(LOG_LEVEL_VERBOSE, &Serial);
  Log.setSuffix([](Print* _logOutput){_logOutput->print('\n');});
  
  wifi.connect(WIFI_SSID, WIFI_PASSWORD, 30, 1000);
  mqttClient.connect(MQTT_HOST, MQTT_PORT, 10, 1000);

  tempHumSensor.begin();
  //sensor.init();
}

void loop()
{
  //String measurementAsJson = sensor.read().toJson();
  //Log.notice(measurementAsJson.c_str());
  //mqttClient.publish(MQTT_TOPIC, measurementAsJson.c_str(), true);
  delay(5000);

  auto measurement = tempHumSensor.read();
  mqttClient.publish(MQTT_HUM_TOPIC, measurement.humidity, true);
  mqttClient.publish(MQTT_TEMP_TOPIC, measurement.temperature, true);
}