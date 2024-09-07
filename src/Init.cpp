#include "Init.h"
Preferences preferences;
IPAddress stWifiIP;
IPAddress stWifigateway;
IPAddress stWifisubnet;
String stWifiSSID;
String stWifiPassword;
boolean stApMode;
byte stEthMac[6];
IPAddress stEthIP;
IPAddress stEthGateway;
IPAddress stEthSubnet;
IPAddress stEthDns;
int stOffSetsTCP[8] = {0,1,2,3,4,5,6,7}; // Inicialize com valores padrão ou específicos
void setupInit()
{
    preferences.begin("config", false);
    //preferences.clear();
    // Load Wi-Fi configuration
    stWifiIP = preferences.getUInt("stWifiIP", IPAddress(192, 168, 1, 3));
    stWifigateway = preferences.getUInt("stWifigateway", IPAddress(192, 168, 1, 1));
    stWifisubnet = preferences.getUInt("stWifisubnet", IPAddress(255, 255, 255, 0));

    stWifiSSID = preferences.getString("stWifiSSID", "VICTOR 2G");
    stWifiPassword = preferences.getString("stWifiPassword", "victorhugo");

    stApMode = preferences.getBool("stApMode", false);

    // Load Ethernet configuration with defaults
    if (preferences.getBytesLength("stEthMac") == sizeof(stEthMac))
    {
        preferences.getBytes("stEthMac", stEthMac, sizeof(stEthMac));
    }
    else
    {
        stEthMac[0] = 0xDE;
        stEthMac[1] = 0xAD;
        stEthMac[2] = 0xBE;
        stEthMac[3] = 0xEF;
        stEthMac[4] = 0xFE;
        stEthMac[5] = 0xED;
    }

    stEthIP = IPAddress(preferences.getUInt("stEthIP", IPAddress(192, 168, 1, 4)));
    stEthGateway = IPAddress(preferences.getUInt("stEthgateway", IPAddress(192, 168, 1, 1)));
    stEthSubnet = IPAddress(preferences.getUInt("stEthsubnet", IPAddress(255, 255, 255, 0)));
    stEthDns = IPAddress(preferences.getUInt("stEthDns", IPAddress(8, 8, 8, 8)));
    if (preferences.getBytesLength("stOffSetsTCP") == 32)
    {
        preferences.getBytes("stOffSetsTCP", stOffSetsTCP, 32);
    }
    else
    {
        // Initialize with default values if no stored values are found
        for (int i = 0; i < 8; i++)
        {
            stOffSetsTCP[i] = i; // Default value
        }
    }

    preferences.end();
}

void configWifi(IPAddress wifiIp, IPAddress wifiGateway, IPAddress wifiSubnet, String wifiSSID, String wifiPassword, boolean wifiApMode)
{
    preferences.begin("config", false);
    // Load Wi-Fi configuration
    preferences.putUInt("stWifiIP", wifiIp);
    preferences.putUInt("stWifigateway", wifiGateway);
    preferences.putUInt("stWifisubnet", wifiSubnet);
    preferences.putString("stWifiSSID", wifiSSID);
    preferences.putString("stWifiPassword", wifiPassword);
    preferences.putBool("stApMode", wifiApMode);
    preferences.end();
}

void configEth(byte ethMac[6], IPAddress ethIp, IPAddress ethGateway, IPAddress ethSubnet, IPAddress ethDns)
{
    preferences.begin("config", false);
    // Load Eth configuration
    preferences.putBytes("stEthMac", ethMac, sizeof(ethMac));
    preferences.putUInt("stEthIP", ethIp);
    preferences.putUInt("stEthgateway", ethGateway);
    preferences.putUInt("stEthsubnet", ethSubnet);
    preferences.putUInt("stEthDns", ethDns);
    preferences.end();
    debug("Dados gravados");
}

void configOffset(int OffSetsTCP[8])
{
    preferences.begin("config", false);
    preferences.putBytes("stOffSetsTCP", OffSetsTCP, 32);
    debug(OffSetsTCP[4]);
    preferences.end();
}

void resetConfig(){
    preferences.clear();
}