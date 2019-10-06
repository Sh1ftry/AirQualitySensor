#ifndef NETWORK_MQTT_H
#define NETWORK_MQTT_H
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

namespace Network
{
    class MQTTClient
    {
        private:
            PubSubClient client;
        public:
            MQTTClient(Wireless network) : client(PubSubClient(network.getClient())) {}
            bool connect(const char* host, uint16_t port, uint8_t maxTries, uint16_t delayMs)
            {
                client.setServer(host, port);
                uint8_t tries = 0;
                while(!client.connected() && tries < maxTries)
                {
                    Log.notice(F("Connecting to MQTT broker"));
                    if(client.connect("AirQualitySensor"))
                    {
                        Log.notice(F("Connected to MQTT broker"));
                    }
                    else
                    {
                        delay(delayMs);
                    }
                    tries++;
                }
                return client.connected();
            }

            void publish(const char* topic, const char* payload, boolean retained = false)
            {
                client.publish(topic, payload, retained);
            }

            void loop()
            {
                client.loop();
            }            
    };
}

#endif /* NETWORK_MQTT_H */