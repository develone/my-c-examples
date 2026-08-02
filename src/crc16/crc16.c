#include <stdio.h>
#include <stdint.h>

// Computes the CRC-16 Modbus checksum for a block of data
uint16_t crc16_modbus(const uint8_t *data, size_t length) {
    uint16_t crc = 0xFFFF; // Initial value for Modbus

    for (size_t i = 0; i < length; i++) {
        crc ^= data[i]; // XOR byte into least sig byte of crc

        for (int j = 0; j < 8; j++) { // Loop over each bit
            if (crc & 0x0001) {       // If the LSB is set
                crc = (crc >> 1) ^ 0xA001; // Shift right and XOR polynomial
            } else {
                crc >>= 1;            // Just shift right
            }
        }
    }
    return crc;
}

int main(void) {
    // Standard test vector "123456789"
    uint8_t test_data[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
    size_t data_len = sizeof(test_data);

    uint16_t result = crc16_modbus(test_data, data_len);

    // Expected Modbus output for "123456789" is 0x4B37
    printf("CRC-16 Modbus: 0x%04X\n", result); 

    return 0;
}