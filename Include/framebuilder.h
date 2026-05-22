#ifndef FRAMEBUILDER_H
#define FRAMEBUILDER_H

#include "common.h"
#include "utils.h"

#define MAX_PAYLOAD 64
#define MAX_FRAME MAX_PAYLOAD + 3

class FrameBuilder {
    uint8_t buffer[MAX_PAYLOAD];
    uint8_t bufferLen = 0;
    uint8_t frame[MAX_FRAME];
    uint8_t frameLen = 0;

   public:
    uint8_t feed(uint8_t in, uint8_t *outFrame);

   private:
    uint8_t flush(uint8_t *outFrame);
    void assemble();
};

#endif