#ifndef ETHERNETSETTINGS_H
#define ETHERNETSETTINGS_H
#include <SPI.h>
#include "settings.h"
#include <Ethernet.h>  // Biblioteca Ethernet para W5500
/*MAC*/
extern byte stEthMac[6];
/*IP*/
extern IPAddress stEthIP;
/*Gateway*/
extern IPAddress stEthGateway;
/*Subnet*/
extern IPAddress stEthSubnet;
/*Dns*/
extern IPAddress stEthDns;

void setupEthernet(byte ethMac[6], IPAddress ethIP, IPAddress ethGateway, IPAddress ethSubnet, IPAddress ethDns);
bool ethernetConnected();
IPAddress getIP();
#endif
