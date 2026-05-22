#include "framebuilder.h"

uint8_t FrameBuilder::feed(uint8_t in, uint8_t *outFrame) {
    if (in == 0x0D) return flush(outFrame);
    if (bufferLen < MAX_PAYLOAD) buffer[bufferLen++] = in;
    return 0;
}

uint8_t FrameBuilder::flush(uint8_t *outFrame) {
    assemble();
    for (int i = 0; i < frameLen; i++) outFrame[i] = frame[i];
    uint8_t len = frameLen;
    bufferLen = 0;
    frameLen = 0;
    return len;
}

void FrameBuilder::assemble() {
    uint8_t crc = calculateCRC8(buffer, bufferLen);
    frame[0] = 0xAA;
    frame[1] = bufferLen;
    for (int i = 0; i < bufferLen; i++) frame[2 + i] = buffer[i];
    frame[2 + bufferLen] = crc;
    frameLen = bufferLen + 3;
}