#include "EthernetSettings.h"

// Endereço MAC (deve ser único na rede)
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
/*IP*/
IPAddress ethIP(192, 168, 1, 4);
/*Gateway*/
IPAddress ethgateway(192, 168, 1, 1);
/*Subnet*/
IPAddress ethsubnet(255, 255, 255, 0);
/*Dns*/
IPAddress ethdns(8, 8, 8, 8);

EthernetClient client;

void prt_hwval(uint8_t refval)
{
    switch (refval)
    {
    case 0:
        Serial.println("No hardware detected.");
        break;
    case 1:
        Serial.println("WizNet W5100 detected.");
        break;
    case 2:
        Serial.println("WizNet W5200 detected.");
        break;
    case 3:
        Serial.println("WizNet W5500 detected.");
        break;
    default:
        Serial.println("UNKNOWN - Update espnow_gw.ino to match Ethernet.h");
    }
}

void prt_ethval(uint8_t refval)
{
    switch (refval)
    {
    case 0:
        Serial.println("Uknown status.");
        break;
    case 1:
        Serial.println("Link flagged as UP.");
        break;
    case 2:
        Serial.println("Link flagged as DOWN. Check cable connection.");
        break;
    default:
        Serial.println("UNKNOWN - Update espnow_gw.ino to match Ethernet.h");
    }
}

void checkConnection()
{
    Serial.print("Checking connection.");
    bool rdy_flag = false;
    for (uint8_t i = 0; i <= 20; i++)
    {
        if ((Ethernet.hardwareStatus() == EthernetNoHardware) || (Ethernet.linkStatus() == LinkOFF))
        {
            Serial.print(".");
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
        Serial.println("\n\r\tHardware fault, or cable problem... cannot continue.");
        Serial.print("Hardware Status: ");
        prt_hwval(Ethernet.hardwareStatus());
        Serial.print("   Cable Status: ");
        prt_ethval(Ethernet.linkStatus());
        while (true)
        {
            delay(10); // Halt.
        }
    }
    else
    {
        Serial.println(" OK");
    }
}

void setupEthernet()
{
    Serial.println("Inicializando Ethernet...");
    Ethernet.init(5);
    Ethernet.begin(mac, ethIP, ethdns, ethgateway, ethsubnet);
    delay(1000); // Pequeno atraso para estabilizar a conexão
    checkConnection();
    Serial.println(getIP());
}

bool ethernetConnected()
{
    return Ethernet.linkStatus() == LinkON;
}

IPAddress getIP()
{
    return Ethernet.localIP();
}
