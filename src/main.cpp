#include <Arduino.h>
#include "wifiSettings.h"
#include "settings.h"
#include "SPIFFSSettings.h"
#include <Arduino_JSON.h>
#include "WebServerSettings.h"
#include "WebsocketSettings.h"
#include "Io.h"
#include "ModbusTCP.h"
#include "EthernetSettings.h"
#include "Init.h"

AsyncWebServer server(80);

void setup()
{
  Serial.begin(115200);
  setupInit();
  setupWifi(stWifiIP, stWifigateway, stWifisubnet, stWifiSSID, stWifiPassword, stApMode);
  setupEthernet(stEthMac, stEthIP, stEthGateway, stEthSubnet, stEthDns);
  setupModbus();
  setupPins();
  iniciarSPIFFS();
  IniciarWebserver(server);
  iniciarWebSocket(server);
}

void loop()
{
  mb.task();
  updateCoils();
  delay(10);
}
