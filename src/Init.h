#ifndef INIT_H
#define INIT_H
#include "WifiSettings.h"
#include "EthernetSettings.h"
#include "ModbusTCP.h"
#include <Preferences.h>
extern Preferences preferences;
void setupInit();
void configOffset(int OffSetsTCP[8]);
void configEth(byte ethMac[6], IPAddress ethIp, IPAddress ethGateway, IPAddress ethSubnet, IPAddress ethDns);
void configWifi(IPAddress wifiIp, IPAddress wifiGateway, IPAddress wifiSubnet, String wifiSSID, String wifiPassword, boolean wifiApMode);
#endif