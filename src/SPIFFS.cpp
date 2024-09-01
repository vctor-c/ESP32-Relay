#include "SPIFFSSettings.h"


// INICIALIZA SPIFFS
void iniciarSPIFFS()
{
    if (!SPIFFS.begin())
    {
        Serial.println("An error has occurred while mounting SPIFFS");
    }
    else
    {
        Serial.println("SPIFFS mounted successfully");

    }
}