#include "ModbusTCP.h"

ModbusEthernet mb;
int offSetsTCPFixed[8] = {
    0, 1, 2, 3, 4, 5, 6, 7
};
void setupModbus() {
    mb.server();
    for (int i = OUT1_COIL; i <= OUT8_COIL; i++) {
        mb.addCoil(offSetsTCPFixed[i]);
    }
    debug("Modbus Server Created...");
}

void updateCoils() {
    for (int i = 0; i < 8; i++) {
        pinUpdate(i, mb.Coil(OUT1_COIL + i));
    }
}
