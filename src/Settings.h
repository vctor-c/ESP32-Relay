#ifndef SETTINGS_H
#define SETTINGS_H
//ativar debug
#define DEBUG 1
#if DEBUG == 1
#define debug(x) Serial.println(x)
#else
#define debug(x)
#endif
#include <Arduino.h>
/*Bibliotecas freeRTOS*/
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
/*Bibliotecas Webserver*/
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>
#endif