#ifndef UART_H
#define UART_H

#include "common.h"

// Configures PA0 (U0Rx) and PA1 (U0Tx) for UART0
// Routed through onboard ICDI — accessible via PuTTY at 9600 baud 8N1
void Init_UART();

// Enables UART0 with TX and RX active
void Enable_UART();

#endif