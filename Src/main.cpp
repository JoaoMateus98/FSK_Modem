#include "PWM.h"
#include "UART.h"
#include "transmitter.h"

int main(void) {
    Init_UART();
    Enable_UART();
    Transmitter tx;

    uint8_t outFrame[MAX_FRAME];

    while (true) {
        if (!(UART0->FR & (1 << 4))) {
            char c = UART0->DR;
            UART0->DR = c;
            uint8_t len = tx.feed(c, outFrame);
            if (len > 0) {
                // frame ready, feed to parser
            }
        }
    }
}
