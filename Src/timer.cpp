#include "common.h"

void Init_Timer() {
    SYSCTL->RCGCTIMER |= (1 << 0);  // enable 16/32 timer module 0
}