#include "PWM.h"
#include "UART.h"

void Init_PWM();
void setPWMFrequency(uint32_t freq);
void Init_UART();
void Enable_UART();

int main(void)
{
    Init_PWM();
    Init_UART();
    Enable_UART();

    while (true)
    {
        echo_PUTTY();
    }
    
}

void echo_PUTTY() {
    if (!(UART0->FR & (1<<4))) // if RX FIFO not empty
        {  
            char c = UART0->DR; // read byte
            UART0->DR = c; // echo back to TX
        }
}