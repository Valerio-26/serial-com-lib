#ifndef SERIAL_COMM_H
#define SERIAL_COMM_H

#include "SerialConfig.h"

#ifdef ARDUINO
#include <Arduino.h>
#else
#include <cstring>
#include <iostream>
#endif

class SerialComm {
    private:
    uint8_t buffer[SERIAL_BUFFER_SIZE];
    uint8_t bufferIndex;

    public:
    SerialComm ();

    void begin ();
    void sendData (const uint8_t* data, uint8_t length);
    bool receiveData (uint8_t* data, uint8_t length);
};

#endif // SERIAL_COMM_H
