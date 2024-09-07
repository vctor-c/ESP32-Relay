#include "WifiSettings.h"


/*Configuracao do wifi*/
void setupWifi(IPAddress wifiIP, IPAddress wifiGateway, IPAddress wifiSubnet, String wifiId, String wifiPassword, boolean apMode)
{
      // Configuracao wifi
   const char *ssid = wifiId.c_str();
   const char *password = wifiPassword.c_str();
   // configuração com conexao ao wifi
   if (apMode)
   {
   WiFi.mode(WIFI_AP);
    WiFi.softAP("Esp", "");
    WiFi.softAPConfig (IPAddress (192,168,4,1), IPAddress (192,168,4,254), IPAddress (255,255,255,0));
    debug("[+] AP Created with IP Gateway ");
    debug(WiFi.softAPIP());
    delay(500);
   }
   else
   { 
      WiFi.mode(WIFI_STA);
      WiFi.config(wifiIP, wifiGateway, wifiSubnet);
      WiFi.begin(ssid, password);
      debug("Connecting to WiFi...");
      while (WiFi.status() != WL_CONNECTED)
      {
         Serial.print('.');
         vTaskDelay(pdTICKS_TO_MS(1000));
      }
      debug("\nConnected to WiFi...");
      debug(WiFi.localIP());
   }

}