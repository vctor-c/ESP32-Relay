#include "SPIFFSSettings.h"


// INICIALIZA SPIFFS
void iniciarSPIFFS()
{
    if (!SPIFFS.begin())
    {
        debug("An error has occurred while mounting SPIFFS");
    }
    else
    {
        debug("SPIFFS mounted successfully");

    }
}