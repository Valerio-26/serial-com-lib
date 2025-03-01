#ifndef SERIAL_CONFIG_H
#define SERIAL_CONFIG_H

// Velocità di comunicazione seriale
#define SERIAL_BAUDRATE 921600

// Numero di byte per pacchetto
#define PACKET_SIZE 8

// Dispositivo seriale per Raspberry Pi (su Arduino non serve)
#ifdef __linux__
    #define SERIAL_DEVICE "/dev/serial0"
#endif

#endif // SERIAL_CONFIG_H
