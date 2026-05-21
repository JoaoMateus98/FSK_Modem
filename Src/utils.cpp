#include "utils.h"

uint8_t calculateCRC8(const uint8_t *data, uint8_t len) {
    uint8_t crc = 0x00;
    uint8_t poly = 0x07;
    for (int i = 0; i < len; i++) {
        crc ^= data[i];
        for (int j = 0; j < 8; j++) {
            if (crc & 0x80)
                crc = (crc << 1) ^ poly;
            else
                crc <<= 1;
        }
    }
    return crc;
}