#ifndef SERIAL_COMM_H
#define SERIAL_COMM_H

#include "SerialConfig.h"

#ifdef ARDUINO
    #include <Arduino.h>
#else
    #include <fcntl.h>
    #include <termios.h>
    #include <unistd.h>
    #include <stdint.h>
#endif

class SerialComm {
public:
    #ifdef ARDUINO
    void begin(HardwareSerial &serialPort) {
        serial = &serialPort;
        serial->begin(SERIAL_BAUDRATE);
    }
    #else
    int fd;
    void begin(const char* device = SERIAL_DEVICE) {
        fd = open(device, O_RDWR | O_NOCTTY);
        if (fd == -1) {
            perror("Serial open error");
        } else {
            struct termios options;
            tcgetattr(fd, &options);
            cfsetispeed(&options, SERIAL_BAUDRATE);
            cfsetospeed(&options, SERIAL_BAUDRATE);
            tcsetattr(fd, TCSANOW, &options);
        }
    }
    #endif

    bool sendData(uint8_t* data, size_t length) {
        #ifdef ARDUINO
        return serial->write(data, length) == length;
        #else
        return write(fd, data, length) == length;
        #endif
    }

    bool receiveData(uint8_t* buffer, size_t length) {
        #ifdef ARDUINO
        return serial->available() >= length && serial->readBytes(buffer, length) == length;
        #else
        return read(fd, buffer, length) == length;
        #endif
    }

private:
    #ifdef ARDUINO
    HardwareSerial* serial;
    #endif
};

#endif // SERIAL_COMM_H
