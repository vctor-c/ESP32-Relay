#ifndef INIT_H
#define INIT_H
#include "WifiSettings.h"
#include "EthernetSettings.h"
#include "ModbusTCP.h"
#include <Preferences.h>
extern Preferences preferences;
void setupInit();
#endif