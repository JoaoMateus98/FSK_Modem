#include "UART.h"

void Init_UART() {
    SYSCTL->RCGCUART |= (1 << 0);
    SYSCTL->RCGCGPIO |= (1 << 0);
    while ((SYSCTL->PRUART & (1 << 0)) == 0) {}
    while ((SYSCTL->PRGPIO & (1 << 0)) == 0) {}

    GPIOA->AFSEL |= (1 << 0) | (1 << 1);
    GPIOA->PCTL &= ~0x000000FF;
    GPIOA->PCTL |= 0x00000011;  // PA0=U0Rx, PA1=U0Tx
    GPIOA->DEN |= (1 << 0) | (1 << 1);
    GPIOA->DIR &= ~(1 << 0);
    GPIOA->DIR |= (1 << 1);
}

void Enable_UART() {
    UART0->CTL &= ~0x01;
    UART0->IBRD = 104;
    UART0->FBRD = 11;
    UART0->LCRH = 0x70;  // 8N1, FIFO enabled
    UART0->CC = 0x00;    // system clock 16MHz
    UART0->CTL |= (1 << 0) | (1 << 8) | (1 << 9);
}