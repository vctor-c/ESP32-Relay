#include "WebServerSettings.h"
#include "SPIFFSSettings.h"
#include "WifiSettings.h"
const char *http_username = "admin";
const char *http_password = "admin";
void IniciarWebserver(AsyncWebServer &server)
{
  // URL RAIZ DO WEBSERVER
// Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    if(!request->authenticate(http_username, http_password))
      return request->requestAuthentication();
    request->send(SPIFFS, "/index.html", "text/html");
  });
  server.serveStatic("/", SPIFFS, "/").setDefaultFile("/index.html");
/*
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(SPIFFS, "/index.html", "text/html"); });
  server.serveStatic("/", SPIFFS, "/").setDefaultFile("/index.html");
  */
  server.begin();
}
