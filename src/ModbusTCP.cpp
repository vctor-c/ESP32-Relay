#include "ModbusTCP.h"

ModbusEthernet mb;
// Definição do array de offsets
void setupModbus(int offSetsTCP[], int size) {
    mb.server();
    for (int i = 0; i < size; i++) {
        mb.addCoil(offSetsTCP[i]);
    }
    debug("Modbus Server Created...");
}

void updateCoils() {
    for (int i = 0; i < 8; i++) {
        pinUpdate(i, mb.Coil(stOffSetsTCP[i]));
    }
}
