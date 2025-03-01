#ifndef SERIAL_CONFIG_H
#define SERIAL_CONFIG_H

#define SERIAL_BAUD_RATE 921600 // Velocità della comunicazione

// Definizione buffer per Arduino (limitato in RAM)
#ifdef ARDUINO
#define SERIAL_BUFFER_SIZE 64
#else
#define SERIAL_BUFFER_SIZE 256
#endif

#endif // SERIAL_CONFIG_H
