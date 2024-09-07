
#ifndef IO_H
#define IO_H
#include "settings.h"

void setupPins();
void pinUpdate(int position, int coilStatus);

const int outPins[] = {
    32, //Relay1
    33, //Relay2
    25, //Relay3
    26, //Relay4
    27, //Relay5
    14, //Relay6
    12, //Relay7
    13  //Relay8
};
const int inPins[] = {
    36, //reset config
};

#endif







