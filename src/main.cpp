#include <Arduino.h>
#include "wifiSettings.h"
#include "settings.h"
#include "SPIFFSSettings.h"
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
  setupModbus(stOffSetsTCP, 8);
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
  if (digitalRead(inPins[0]) == HIGH) {
    resetConfig();  // Executa a função quando o pino estiver em verdadeiro
    debug("Reset config");
  }
}
