#include "WifiSettings.h"

// gambiarra de preguiçoso pra o reconnect caso o wifi perca conexão
const char *ssid;
const char *password;
void initWifiAP()
{
   WiFi.mode(WIFI_AP);
   WiFi.softAP("Relay Board", "");
   WiFi.softAPConfig(IPAddress(192, 168, 1, 2), IPAddress(192, 168, 4, 254), IPAddress(255, 255, 255, 0));
   debug("[+] AP Created with IP Gateway ");
   debug(WiFi.softAPIP());
   vTaskDelay(pdTICKS_TO_MS(500));
}

boolean initWifiSTA(IPAddress wifiIP, IPAddress wifiGateway, IPAddress wifiSubnet, String wifiId, String wifiPassword)
{
   // Configuracao wifi
   ssid = wifiId.c_str();
   password = wifiPassword.c_str();
   int attempts = 0;
   WiFi.mode(WIFI_STA);
   WiFi.config(wifiIP, wifiGateway, wifiSubnet);
   WiFi.begin(ssid, password);
   debug("Connecting to WiFi...");
   while (WiFi.status() != WL_CONNECTED)
   {
      Serial.print('.');
      vTaskDelay(pdTICKS_TO_MS(1000));
      attempts += 1;
      if (attempts == 3)
      {
         debug("Failed to Connect...");
         return false;
      }
   }
   debug("\nConnected to WiFi...");
   debug(WiFi.localIP());
   return true;
}

void WiFiStationDisconnected(WiFiEvent_t event, WiFiEventInfo_t info)
{
   Serial.println(info.wifi_sta_disconnected.reason);
   WiFi.begin(ssid, password);
}

/*Configuracao do wifi*/
void setupWifi(IPAddress wifiIP, IPAddress wifiGateway, IPAddress wifiSubnet, String wifiId, String wifiPassword, boolean apMode)
{
   // configuração com conexao ao wifi
   if (apMode)
   {
      initWifiAP();
   }
   else
   {
      if (!initWifiSTA(wifiIP, wifiGateway, wifiSubnet, wifiId, wifiPassword))
      {
         initWifiAP();
      }
      else
      {
         WiFi.onEvent(WiFiStationDisconnected, WiFiEvent_t::ARDUINO_EVENT_WIFI_STA_DISCONNECTED);
      }
   }
}
