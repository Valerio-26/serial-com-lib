// SerialComm.cpp - Implementazione per Arduino e Raspberry Pi
#include "SerialComm.h"
#ifdef ARDUINO
#include <Arduino.h>
#else
#include <wiringSerial.h>
#include <stdio.h>
#include <string.h>
#endif

SerialComm::SerialComm() {}

void SerialComm::begin(unsigned long baudrate) {
#ifdef ARDUINO
    Serial.begin(baudrate);
#else
    int fd = serialOpen("/dev/serial0", baudrate);
    if (fd == -1) {
        perror("Errore apertura seriale");
    }
#endif
}

bool SerialComm::sendPacket(uint8_t command, uint8_t* data, uint8_t length) {
    if (length > MAX_PAYLOAD_SIZE) return false;
    
    Packet packet;
    packet.startByte = START_BYTE;
    packet.command = command;
    packet.length = length;
    memcpy(packet.payload, data, length);
    packet.checksum = calculateChecksum(packet);
    
#ifdef ARDUINO
    Serial.write((uint8_t*)&packet, sizeof(Packet));
#else
    int fd = serialOpen("/dev/serial0", 921600);
    if (fd != -1) {
        write(fd, &packet, sizeof(Packet));
        serialClose(fd);
    }
#endif
    return true;
}

bool SerialComm::receivePacket(Packet &packet) {
#ifdef ARDUINO
    if (Serial.available() >= sizeof(Packet)) {
        Serial.readBytes((char*)&packet, sizeof(Packet));
        return packet.startByte == START_BYTE && packet.checksum == calculateChecksum(packet);
    }
#else
    int fd = serialOpen("/dev/serial0", 921600);
    if (fd != -1 && serialDataAvail(fd) >= sizeof(Packet)) {
        read(fd, &packet, sizeof(Packet));
        serialClose(fd);
        return packet.startByte == START_BYTE && packet.checksum == calculateChecksum(packet);
    }
#endif
    return false;
}

uint8_t SerialComm::calculateChecksum(Packet &packet) {
    uint8_t sum = packet.startByte + packet.command + packet.length;
    for (uint8_t i = 0; i < packet.length; i++) {
        sum += packet.payload[i];
    }
    return sum;
}