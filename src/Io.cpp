#include "Io.h"

void setupPins() {
    for (int pin : outPins) {
        pinMode(pin, OUTPUT);
    }
    pinMode(inPins[0], INPUT);
}

void pinUpdate(int position, int coilStatus) {
        digitalWrite(outPins[position], coilStatus);
}
