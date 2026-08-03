#include <stdio.h>
#include <stdint.h>

#define CRC32_INIT                  ((uint32_t)-1l)

#define DATA_TO_CHECK_LEN           9
#define CRC32_LEN                   4
#define TOTAL_LEN                   (DATA_TO_CHECK_LEN + CRC32_LEN)

// commonly used crc test data and also space for the crc value
static uint8_t src[TOTAL_LEN] = { 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x00, 0x00, 0x00, 0x00 };
static uint8_t dummy_dst[1];

// This uses a standard polynomial with the alternate 'reversed' shift direction.
// It is possible to use a non-reversed algorithm here but the DMA sniff set-up
// below would need to be modified to remain consistent and allow the check to pass.
static uint32_t soft_crc32_block(uint32_t crc, uint8_t *bytp, uint32_t length) {
    while(length--) {
        uint32_t byte32 = (uint32_t)*bytp++;

        for (uint8_t bit = 8; bit; bit--, byte32 >>= 1) {
            crc = (crc >> 1) ^ (((crc ^ byte32) & 1ul) ? 0xEDB88320ul : 0ul);
        }
    }
    return crc;
}


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
    uint8_t test_data[] = {'W', 'e', 'l', 'c', 'o', 'm', 'e', ' ', 't', 'o', ' ', 't', 'h', 'e', ' ', 'W', 'o', 'r', 'k', 's', 'h', 'o', 'p','!'};
    //uint8_t test_data[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
    size_t data_len = sizeof(test_data);
    printf("%s 0x%x \n",test_data,data_len);
    uint16_t result = crc16_modbus(test_data, data_len);

    // Expected Modbus output for "123456789" is 0x4B37
    printf("CRC-16 Modbus: 0x%04X\n", result);
    // calculate and append the crc
    uint32_t crc_res;
    crc_res = soft_crc32_block(CRC32_INIT, src, DATA_TO_CHECK_LEN);
    printf("0x%hx\n",crc_res);
    return 0;
}
