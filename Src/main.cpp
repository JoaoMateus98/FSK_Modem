#include "PWM.h"
#include "UART.h"
#include "framebuilder.h"
#include "transmitter.h"

int main(void) {
    Init_UART();
    Enable_UART();

    FrameBuilder builder;
    Transmitter transmitter;
    uint8_t frameBuffer[MAX_FRAME];

    while (true) {
        if (!(UART0->FR & (1 << 4))) {
            char c = UART0->DR;
            UART0->DR = c;
            uint8_t len = builder.feed(c, frameBuffer);
            if (len > 0) { transmitter.load(frameBuffer, len); }
        }
    }
}
