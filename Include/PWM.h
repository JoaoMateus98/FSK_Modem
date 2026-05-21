#ifndef PWM_H
#define PWM_H

#include "TM4C123GH6PM.h"
#include <stdint.h>

void Init_PWM(void);
void setPWMFrequency(uint32_t freq);

#endif