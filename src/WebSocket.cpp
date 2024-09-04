#include "WebsocketSettings.h"

/* VARIAVEL JSON PARA TRANSFERIR DADOS PARA WEBSERVER*/
JSONVar leituras;
/* Objeto WebSocket*/
AsyncWebSocket ws("/ws");
/*Variaveis para armazenamento do handle das tasks*/
TaskHandle_t taskEnvioWebSocket = NULL;
/*prototipos das tasks*/
void vTaskenviarLeituras(void *pvParameters);

void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len);

String leiturasJson();

void notificaClientes(String leiturasSensores);

void handleWebSocketMessage(void *arg, uint8_t *data, size_t len);

void iniciarWebSocket(AsyncWebServer &server)
{
    ws.onEvent(onEvent);
    server.addHandler(&ws);
    xTaskCreatePinnedToCore(vTaskenviarLeituras, "TaskEnvioWebSocket", configMINIMAL_STACK_SIZE + 1024, NULL, 1, &taskEnvioWebSocket, PRO_CPU_NUM);
}
String macToString(const byte mac[6]) {
    char macStr[18];
    snprintf(macStr, sizeof(macStr), "%02X:%02X:%02X:%02X:%02X:%02X", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
    return String(macStr);
}

String ipToString(const IPAddress &ip) {
    return ip.toString();
}
/*PEGA OS VALORES DE LEITURAS E RETORNA UMA STRING JSON*/
String leiturasJson()
{

    leituras["MAC"] = macToString(stEthMac);
    leituras["IP"] = ipToString(stEthIP);
    leituras["Gateway"] = ipToString(stEthGateway);
    leituras["Subnet"] = ipToString(stEthSubnet);
    leituras["DNS"] = ipToString(stEthDns);

    String jsonString = JSON.stringify(leituras);
    return jsonString;
}
/*Notifica clientes de uma mudanca*/
void notificaClientes(String leitura)
{
    ws.textAll(leitura);
}
/*Quando o esp32 recebe um "getLeituras" envia os valores de leitura*/
void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
    AwsFrameInfo *info = (AwsFrameInfo *)arg;
    if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
        data[len] = 0;
        String message = (char *)data;
        
        if (strcmp((char *)data, "getLeituras") == 0) {
            String leitura = leiturasJson();
            Serial.println(leitura);  // Print the JSON string to the serial monitor
            notificaClientes(leitura);
        }
    }
}
/*Lida com eventos do Websocket*/
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

/*envia Leitura a cada 1 segundo*/
void vTaskenviarLeituras(void *pvParameters)
{
    TickType_t ultimoCiclo;
    /*frequencia em ticks que sera convertido em ms*/
    const TickType_t frequencia = 5000;

    /*Inicializa ultimoCiclo com o valor atual de ticks*/
    ultimoCiclo = xTaskGetTickCount();

    for (;;)
    {
        /*espera por o proximo ciclo*/
        vTaskDelayUntil(&ultimoCiclo, (frequencia / portTICK_RATE_MS));
        /*Pega leituras de sensores e envia para clientes*/
        String leiturasSensores = leiturasJson();
        notificaClientes(leiturasSensores);
        ws.cleanupClients();
    }
}
