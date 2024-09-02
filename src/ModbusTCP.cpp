#include "ModbusTCP.h"

ModbusEthernet mb;
void setupModbus() {
    mb.server();
    for (int i = OUT1_COIL; i <= OUT8_COIL; i++) {
        mb.addCoil(offSetsTCP[i]);
    }
    debug("Modbus Server Created...");
}

void updateCoils() {
    for (int i = 0; i < 8; i++) {
        pinUpdate(i, mb.Coil(OUT1_COIL + i));
    }
}
