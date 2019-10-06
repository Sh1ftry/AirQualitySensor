#include <Arduino.h>
#include <ArduinoLog.h>
#include "air_quality/Sensor.h"
#include "network/Wireless.h"
#include "network/MQTTClient.h"

const uint8_t SENSOR_RX=12, SENSOR_TX=13;
const uint16_t BAUD_RATE=9600;

const char* WIFI_SSID = "";
const char* WIFI_PASSWORD = "";
const char* MQTT_HOST = "broker.hivemq.com";
const uint16_t MQTT_PORT = 1883;
const char* MQTT_TOPIC = "sensors/air_quality_sensor";

AirQuality::Sensor sensor(SENSOR_RX, SENSOR_TX);
Network::Wireless wifi;
Network::MQTTClient mqttClient(wifi);

void setup()
{
  Serial.begin(BAUD_RATE);
  
  Log.begin(LOG_LEVEL_VERBOSE, &Serial);
  Log.setSuffix([](Print* _logOutput){_logOutput->print('\n');});
  
  wifi.connect(WIFI_SSID, WIFI_PASSWORD, 30, 1000);
  mqttClient.connect(MQTT_HOST, MQTT_PORT, 10, 1000);

  sensor.init();
}

void loop()
{
  String measurementAsJson = sensor.read().toJson();
  Log.notice(measurementAsJson.c_str());
  mqttClient.publish(MQTT_TOPIC, measurementAsJson.c_str(), true);
  delay(5000);
}