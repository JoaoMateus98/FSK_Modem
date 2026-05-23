#ifndef TRANSMITTER_H
#define TRANSMITTER_H

#include <cstring>
#include <memory>

#include "common.h"

class State;

class Transmitter {
    friend class WaitingState;
    friend class SendingByteState;
    friend class SendingBitState;
    friend class CleanupState;

   private:
    uint8_t frameBuffer[MAX_FRAME];
    uint8_t bytesLeft = 0;
    uint8_t currentByte = 0;
    uint8_t bitsLeft = 0;
    std::unique_ptr<State> state_;

   public:
    Transmitter() {}
    void load(uint8_t* frame, uint8_t len);
    void tick();

   private:
    void setState(std::unique_ptr<State> s) { state_ = std::move(s); }
    uint8_t getByte();
};

#endif