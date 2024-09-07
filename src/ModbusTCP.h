#ifndef MODBUSTCP_H
#define MODBUSTCP_H

#include "settings.h"
#include "CoilOut.h"
#include "Io.h"
#include "EthernetSettings.h"
/*Biblioteca Modbus*/
#include <ModbusEthernet.h>

void setupModbus(int offSetsTCP[], int size);
void updateCoils();

// Declaração externa de `mb`
extern ModbusEthernet mb;

// Definição de Offset de coils para saidas dos relês 
extern int stOffSetsTCP[8];

#endif
