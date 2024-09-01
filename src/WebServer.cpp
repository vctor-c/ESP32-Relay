#include "WebServerSettings.h"
#include "SPIFFSSettings.h"
#include "WifiSettings.h"

void IniciarWebserver(AsyncWebServer &server)
{
  // URL RAIZ DO WEBSERVER
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(SPIFFS, "/index.html", "text/html"); });
  server.serveStatic("/", SPIFFS, "/");
  server.begin();
}
