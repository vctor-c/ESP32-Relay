#include <ArduinoJson.h>
#include "WebsocketSettings.h"

/* VARIAVEL JSON PARA TRANSFERIR DADOS PARA WEBSERVER*/
DynamicJsonDocument leituras(1024); // Ajuste o tamanho conforme necessário
DynamicJsonDocument recebido(1024); // Ajuste o tamanho conforme necessário

/* Objeto WebSocket*/
AsyncWebSocket ws("/ws");

/*Variaveis para armazenamento do handle das tasks*/
TaskHandle_t taskEnvioWebSocket = NULL;

/*Prototipos das tasks*/
// void vTaskenviarLeituras(void *pvParameters);

void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len);

String leiturasJsonEth();
String leiturasJsonWifi();
String leiturasJsonProtocol();
void notificaClientes(const String &leiturasSensores);
void handleWebSocketMessage(void *arg, uint8_t *data, size_t len);
void processarJsonRecebido(const String &jsonString);

/*Inicia o WebSocket*/
void iniciarWebSocket(AsyncWebServer &server)
{
    ws.onEvent(onEvent);
    server.addHandler(&ws);
    // xTaskCreatePinnedToCore(vTaskenviarLeituras, "TaskEnvioWebSocket", configMINIMAL_STACK_SIZE + 1024, NULL, 1, &taskEnvioWebSocket, PRO_CPU_NUM);
}

/*Converte o MAC para uma String*/
String macToString(const byte mac[6])
{
    char macStr[18];
    snprintf(macStr, sizeof(macStr), "%02X:%02X:%02X:%02X:%02X:%02X", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
    return String(macStr);
}

/*Converte o IP para uma String*/
String ipToString(const IPAddress &ip)
{
    return ip.toString();
}

/*Gera uma String JSON para as leituras de Ethernet*/
String leiturasJsonEth()
{
    leituras.clear();
    leituras["Leituras"] = "Eth";
    leituras["EthMAC"] = macToString(stEthMac);
    leituras["EthIP"] = ipToString(stEthIP);
    leituras["EthGateway"] = ipToString(stEthGateway);
    leituras["EthSubnet"] = ipToString(stEthSubnet);
    leituras["EthDNS"] = ipToString(stEthDns);

    String jsonString;
    serializeJson(leituras, jsonString);
    return jsonString;
}

/*Gera uma String JSON para as leituras de Wi-Fi*/
String leiturasJsonWifi()
{
    leituras.clear();
    leituras["Leituras"] = "Wifi";
    leituras["WifiIP"] = ipToString(stWifiIP);
    leituras["WifiGateway"] = ipToString(stWifigateway);
    leituras["WifiSubnet"] = ipToString(stWifisubnet);
    leituras["WifiSSID"] = stWifiSSID;
    leituras["WifiapMode"] = stApMode;

    String jsonString;
    serializeJson(leituras, jsonString);
    return jsonString;
}

/*Gera uma String JSON para as leituras de Protocolo*/
String leiturasJsonProtocol()
{
    leituras.clear();
    leituras["Leituras"] = "Protocol";
    leituras["Relay1"] = stOffSetsTCP[0];
    leituras["Relay2"] = stOffSetsTCP[1];
    leituras["Relay3"] = stOffSetsTCP[2];
    leituras["Relay4"] = stOffSetsTCP[3];
    leituras["Relay5"] = stOffSetsTCP[4];
    leituras["Relay6"] = stOffSetsTCP[5];
    leituras["Relay7"] = stOffSetsTCP[6];
    leituras["Relay8"] = stOffSetsTCP[7];

    String jsonString;
    serializeJson(leituras, jsonString);
    return jsonString;
}

/*Notifica todos os clientes com a leitura fornecida*/
void notificaClientes(const String &leitura)
{
    ws.textAll(leitura);
}

IPAddress stringToIp(const String &ipStr)
{
    IPAddress ip;
    if (ip.fromString(ipStr))
    {
        return ip; // Retorna o IP se a conversão for bem-sucedida
    }
    else
    {
        // Se a conversão falhar, você pode definir um IP padrão ou lidar com o erro
        debug("falhou");
        return IPAddress(1, 0, 0, 0); // IP padrão indicando erro
    }
}

// Função para converter string MAC em um array de bytes
byte *stringToMac(const String &macStr)
{
    static byte mac[6]; // Array estático para armazenar o MAC
    // Verifica se a string tem o comprimento correto
    if (macStr.length() != 17)
    {
        return nullptr; // Retorna nullptr se a string estiver no formato errado
    }

    int byteValues[6];
    int pos = 0;

    // Converte cada byte da string para um valor numérico
    for (int i = 0; i < 6; i++)
    {
        if (sscanf(macStr.c_str() + pos, "%2X", &byteValues[i]) != 1)
        {
            return nullptr; // Retorna nullptr se a conversão falhar
        }
        pos += 3; // Avança 2 caracteres e 1 separador
    }

    // Copia os valores para o array de bytes
    for (int i = 0; i < 6; i++)
    {
        mac[i] = byteValues[i];
    }

    return mac; // Retorna o array de bytes
}

/*Processa o JSON recebido e atualiza as variáveis correspondentes*/
void processarJsonRecebido(const String &jsonString)
{
    DynamicJsonDocument doc(1024); // Ajuste o tamanho se necessário
    DeserializationError error = deserializeJson(doc, jsonString);

    if (error)
    {
        Serial.println("Erro ao analisar JSON!");
        return;
    }
    if (doc["ethMac"])
    {
        String ethDns = doc["ethDns"].as<String>();
        String ethGateway = doc["ethGateway"].as<String>();
        String ethIP = doc["ethIP"].as<String>();
        String ethMac = doc["ethMac"].as<String>();
        String ethSubnet = doc["ethSubnet"].as<String>();
        // Atualize suas variáveis com os novos valores recebidos
        byte *macResult = stringToMac(ethMac);
        IPAddress ipResult = stringToIp(ethIP);
        IPAddress gatewayResult = stringToIp(ethGateway);
        IPAddress subnetResult = stringToIp(ethSubnet);
        IPAddress dnsResult = stringToIp(ethDns);
        configEth(macResult, ipResult, gatewayResult, subnetResult, dnsResult);
    }
    else if (doc["wifiIP"])
    {
        String wifiIP = doc["wifiIP"].as<String>();
        String wifiGateway = doc["wifiGateway"].as<String>();
        String wifiSubnet = doc["wifiSubnet"].as<String>();
        String wifiSSID = doc["wifiSSID"].as<String>();
        String inputWifiPass = doc["wifiPass"].as<String>();
        boolean wifiApMode = doc["wifiModeOP"];

        // Atualize suas variáveis ou estruturas com os novos valores recebidos
        IPAddress WifiIPResult = stringToIp(wifiIP);
        IPAddress stWifigatewayResult = stringToIp(wifiGateway);
        IPAddress stWifisubnetResult = stringToIp(wifiSubnet);

        configWifi(WifiIPResult, stWifigatewayResult, stWifisubnetResult, wifiSSID, inputWifiPass, wifiApMode);
    }
    else if (doc["relay1"])
    {
        int OffSetsTCP[8];
        OffSetsTCP[0] = doc["relay1"].as<int>();
        OffSetsTCP[1] = doc["relay2"].as<int>();
        OffSetsTCP[2] = doc["relay3"].as<int>();
        OffSetsTCP[3] = doc["relay4"].as<int>();
        OffSetsTCP[4] = doc["relay5"].as<int>();
        OffSetsTCP[5] = doc["relay6"].as<int>();
        OffSetsTCP[6] = doc["relay7"].as<int>();
        OffSetsTCP[7] = doc["relay8"].as<int>();
        configOffset(OffSetsTCP);
    }
}

/*Lida com mensagens WebSocket*/
void handleWebSocketMessage(void *arg, uint8_t *data, size_t len)
{
    AwsFrameInfo *info = (AwsFrameInfo *)arg;
    if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT)
    {
        data[len] = 0;
        String message = (char *)data;
        if (message == "getLeiturasEth")
        {
            String leitura = leiturasJsonEth();
            Serial.println(leitura); // Print the JSON string to the serial monitor
            notificaClientes(leitura);
        }
        else if (message == "getLeiturasWifi")
        {
            String leitura = leiturasJsonWifi();
            Serial.println(leitura); // Print the JSON string to the serial monitor
            notificaClientes(leitura);
        }
        else if (message == "getLeiturasProtocol")
        {
            String leitura = leiturasJsonProtocol();
            Serial.println(leitura); // Print the JSON string to the serial monitor
            notificaClientes(leitura);
        }
        else
        {
            // Se a mensagem não for um comando de leitura, assume-se que é um JSON a ser processado
            Serial.println("Recebido JSON:");
            Serial.println(message);
            processarJsonRecebido(message);
        }
    }
}

/*Lida com eventos do WebSocket*/
void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len)
{
    switch (type)
    {
    case WS_EVT_CONNECT:
        Serial.printf("Cliente WebSocket #%u conectado de %s\n", client->id(), client->remoteIP().toString().c_str());
        break;
    case WS_EVT_DISCONNECT:
        Serial.printf("Cliente WebSocket #%u desconectado\n", client->id());
        break;
    case WS_EVT_DATA:
        handleWebSocketMessage(arg, data, len);
        break;
    case WS_EVT_PONG:
    case WS_EVT_ERROR:
        break;
    }
}

/*envia Leitura a cada 1 segundo
void vTaskenviarLeituras(void *pvParameters)
{
    TickType_t ultimoCiclo;
    //frequencia em ticks que sera convertido em ms
    const TickType_t frequencia = 5000;

    //Inicializa ultimoCiclo com o valor atual de ticks
    ultimoCiclo = xTaskGetTickCount();

    for (;;)
    {
        //espera por o proximo ciclo
        vTaskDelayUntil(&ultimoCiclo, (frequencia / portTICK_RATE_MS));
        //Pega leituras de sensores e envia para clientes
        String leiturasSensores = leiturasJsonEth();
        notificaClientes(leiturasSensores);
        ws.cleanupClients();
    }
}*/
