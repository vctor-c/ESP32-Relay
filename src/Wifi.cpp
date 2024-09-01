#include "WifiSettings.h"
/*Credenciais do Wifi*/
const char *wifiId = "VICTOR 2G";
const char *wifiPassword = "victorhugo";
/*Configuracao do wifi*/
/*IP*/
IPAddress IP(192, 168, 1, 3);
/*Gateway*/
IPAddress gateway(192, 168, 1, 1);
/*Subnet*/
IPAddress subnet(255, 255, 255, 0);

void setupWifi()
{
    // Configuracao wifi 
    const char *ssid = wifiId;
    const char *password = wifiPassword;
    //inicializar wifi
    WiFi.mode(WIFI_STA);
     // Configures static IP address
  if (!WiFi.config(IP, gateway, subnet)) {
    Serial.println("STA Failed to configure");
  }
  //configuração com conexao ao wifi
  
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED)
  {
     Serial.print('.');
     vTaskDelay(pdTICKS_TO_MS(1000));
  }
  Serial.println("\nConnected to WiFi...");
  Serial.println(WiFi.localIP());
  
 //configuração como AP
 //WiFi.softAP(ssid);
}