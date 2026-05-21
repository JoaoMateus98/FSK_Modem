#include "PWM.h"

void Init_PWM() {
    SYSCTL->RCGCPWM |= (1 << 1);
    SYSCTL->RCGCGPIO |= (1 << 5);
    SYSCTL->RCC &= ~0x00100000;  // route system clock directly to PWM, no prescaler

    while ((SYSCTL->PRPWM & (1 << 1)) == 0) {}
    while ((SYSCTL->PRGPIO & (1 << 5)) == 0) {}

    // PF0 is the NMI pin and requires explicit unlock before use
    GPIOF->LOCK = 0x4C4F434B;
    GPIOF->CR |= (1 << 0);

    GPIOF->AFSEL |= (1 << 0);
    GPIOF->PCTL &= ~0x0000000F;
    GPIOF->PCTL |= 0x00000005;  // PMC0=5 → M1PWM4
    GPIOF->DEN |= (1 << 0);

    PWM1->_2_CTL = 0;
    PWM1->_2_GENA = 0x0000008C;  // set on reload, clear on CMPA — 50% duty cycle
    PWM1->_2_LOAD = 13333;       // 1200 Hz mark tone (16MHz / 13333)
    PWM1->_2_CMPA = 6666;
    PWM1->_2_CTL = 1;
    PWM1->ENABLE |= (1 << 4);
}

// switches FSK tone — call from baud clock ISR per bit
void setPWMFrequency(uint32_t freq) {
    uint32_t load = 16000000 / freq;
    PWM1->_2_LOAD = load - 1;
    PWM1->_2_CMPA = (load / 2) - 1;
}