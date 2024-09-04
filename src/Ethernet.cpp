#include "EthernetSettings.h"

EthernetClient client;

void prt_hwval(uint8_t refval)
{
    switch (refval)
    {
    case 0:
        debug("No hardware detected.");
        break;
    case 1:
        debug("WizNet W5100 detected.");
        break;
    case 2:
        debug("WizNet W5200 detected.");
        break;
    case 3:
        debug("WizNet W5500 detected.");
        break;
    default:
        debug("UNKNOWN - Update espnow_gw.ino to match Ethernet.h");
    }
}

void prt_ethval(uint8_t refval)
{
    switch (refval)
    {
    case 0:
        debug("Uknown status.");
        break;
    case 1:
        debug("Link flagged as UP.");
        break;
    case 2:
        debug("Link flagged as DOWN. Check cable connection.");
        break;
    default:
        debug("UNKNOWN - Update espnow_gw.ino to match Ethernet.h");
    }
}

void checkConnection()
{
    debug("Checking connection.");
    bool rdy_flag = false;
    for (uint8_t i = 0; i <= 20; i++)
    {
        if ((Ethernet.hardwareStatus() == EthernetNoHardware) || (Ethernet.linkStatus() == LinkOFF))
        {
            debug(".");
            rdy_flag = false;
            delay(80);
        }
        else
        {
            rdy_flag = true;
            break;
        }
    }
    if (rdy_flag == false)
    {
        debug("\n\r\tHardware fault, or cable problem... cannot continue.");
        debug("Hardware Status: ");
        prt_hwval(Ethernet.hardwareStatus());
        debug("   Cable Status: ");
        prt_ethval(Ethernet.linkStatus());
        while (true)
        {
            delay(10); // Halt.
        }
    }
    else
    {
        debug(" OK");
    }
}

void setupEthernet(byte ethMac[6], IPAddress ethIP, IPAddress ethGateway, IPAddress ethSubnet, IPAddress ethDns)
{
    debug("Inicializando Ethernet...");
    Ethernet.init(5);
    Ethernet.begin(ethMac, ethIP, ethDns, ethGateway, ethSubnet);
    delay(1000); // Pequeno atraso para estabilizar a conexão
    checkConnection();
    debug(getIP());
}

bool ethernetConnected()
{
    return Ethernet.linkStatus() == LinkON;
}

IPAddress getIP()
{
    return Ethernet.localIP();
}
