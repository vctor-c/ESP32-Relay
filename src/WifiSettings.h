#ifndef WIFISETTINGS_H
#define WIFISETTINGS_H
#include <WiFi.h>
#include "settings.h"
/*Configuracao do wifi*/
/*IP*/
extern IPAddress stWifiIP;
/*Gateway*/
extern IPAddress stWifigateway;
/*Subnet*/
extern IPAddress stWifisubnet;
/*SSID*/
extern String stWifiSSID;
/*Password*/
extern String stWifiPassword;
/*Opmode*/
extern boolean stApMode;
void setupWifi(IPAddress wifiIP, IPAddress wifiGateway, IPAddress wifiSubnet, String wifiId, String wifiPassword, boolean apMode);
#endif