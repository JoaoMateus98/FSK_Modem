#include "UART.h"

void Init_UART() {
    SYSCTL->RCGCUART |= (1 << 0); // enable clock for UART0
    SYSCTL->RCGCGPIO |= (1 << 0); // enable clock for Port A
    while ((SYSCTL->PRUART  & (1<<0)) == 0) {}  // wait UART0 ready
    while ((SYSCTL->PRGPIO  & (1<<0)) == 0) {}  // wait PORTA ready
    GPIOA->AFSEL |= (1<<0) | (1<<1);  // alternate function PA0, PA1
    GPIOA->PCTL  &= ~0x000000FF;      // clear PCTL for PA0 and PA1
    GPIOA->PCTL  |=  0x00000011;      // PA0=1 (U0Rx), PA1=1 (U0Tx)
    GPIOA->DEN   |= (1<<0) | (1<<1);  // digital enable
    GPIOA->DIR   &= ~(1<<0);          // PA0 input  (Rx)
    GPIOA->DIR   |=  (1<<1);          // PA1 output (Tx)
}

void Enable_UART() {
    UART0->CTL  &= ~0x01;
    UART0->IBRD  = 104;
    UART0->FBRD  = 11;
    UART0->LCRH  = 0x70;
    UART0->CC    = 0x00;
    UART0->CTL  |= (1<<0) | (1<<8) | (1<<9);
}