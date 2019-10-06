#ifndef NETWORK_WIFI_H
#define NETWORK_WIFI_H
#include <ESP8266WiFi.h>
#include <ArduinoLog.h>

namespace Network
{
    class Wireless
    {
        private:
            WiFiClient client;
        public:
            bool connect(const String& ssid, const String& password, int maxTries, int delayMs)
            {   
                WiFi.begin(ssid, password);
                int tries = 0;
                
                while(WiFi.status() != WL_CONNECTED && tries < maxTries)
                {
                    Log.notice(F("Connecting to network..."));
                    delay(delayMs);
                    tries++;
                }
                
                if(WiFi.status() != WL_CONNECTED)
                {
                    Log.notice(F("Could not connect"));
                    WiFi.disconnect();
                }
                else
                {
                    Log.notice(F("Connected to network"));
                }
                
                return WiFi.status() == WL_CONNECTED;
            }
            WiFiClient& getClient()
            {
                return client;
            }
    };
}

#endif /* NETWORK_WIFI_H */