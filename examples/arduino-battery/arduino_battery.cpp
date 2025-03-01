#include "SerialComm.h"
#include <Arduino.h>

SerialComm serialComm;

void setup() {
    serialComm.begin(Serial);
}

void loop() {
    uint8_t receivedData[8];
    if (serialComm.receiveData(receivedData, 8)) {
        if (receivedData[0] == 1) {  // Richiesta livello batteria
            uint8_t batteryLevel = 75;  // Simuliamo 75%
            uint8_t response[8] = { batteryLevel, 0, 0, 0, 0, 0, 0, 0 };
            serialComm.sendData(response, 8);
        }
    }
}
