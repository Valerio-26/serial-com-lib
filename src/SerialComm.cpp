#include "SerialComm.h"

SerialComm::SerialComm () : bufferIndex (0) {
}

void SerialComm::begin () {
#ifdef ARDUINO
    Serial.begin (SERIAL_BAUD_RATE);
#else
    std::cout << "Serial initialized at " << SERIAL_BAUD_RATE << " baud." << std::endl;
#endif
}

void SerialComm::sendData (const uint8_t* data, uint8_t length) {
#ifdef ARDUINO
    Serial.write (data, length);
#else
    std::cout << "Sending: ";
    for (uint8_t i = 0; i < length; i++) {
        std::cout << std::hex << static_cast<int> (data[i]) << " ";
    }
    std::cout << std::dec << std::endl;
#endif
}

bool SerialComm::receiveData (uint8_t* data, uint8_t length) {
#ifdef ARDUINO
    if (Serial.available () >= length) {
        Serial.readBytes (data, length);
        return true;
    }
#else
    // Simulazione di ricezione su Raspberry Pi
    std::memcpy (data, "TEST", length);
    return true;
#endif
    return false;
}
