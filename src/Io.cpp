#include "Io.h"

void setupPins() {
    for (int pin : outPins) {
        pinMode(pin, OUTPUT);
    }
}

void pinUpdate(int position, int coilStatus) {
        digitalWrite(outPins[position], coilStatus);
}
