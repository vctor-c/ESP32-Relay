#include "WifiSettings.h"

/*Configuracao do wifi*/
void setupWifi(IPAddress wifiIP, IPAddress wifiGateway, IPAddress wifiSubnet, String wifiId, String wifiPassword, boolean apMode)
{
   // Configuracao wifi
   const char *ssid = wifiId.c_str();
   const char *password = wifiPassword.c_str();
   // inicializar wifi
   WiFi.mode(WIFI_STA);
   // Configures static IP address
   if (!WiFi.config(wifiIP, wifiGateway, wifiSubnet))
   {
      debug("STA Failed to configure");
   }

   // configuração com conexao ao wifi
   if (apMode)
   {
      // configuração como AP
      WiFi.softAP(ssid, password);
      debug("AccessPoint Created...");
      debug(WiFi.localIP());
   }
   else
   {
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