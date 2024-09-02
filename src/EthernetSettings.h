#ifndef ETHERNETSETTINGS_H
#define ETHERNETSETTINGS_H
#include <SPI.h>
#include "settings.h"
#include <Ethernet.h>  // Biblioteca Ethernet para W5500
void setupEthernet();
bool ethernetConnected();
IPAddress getIP();
#endif
