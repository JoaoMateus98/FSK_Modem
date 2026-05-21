#ifndef PWM_H
#define PWM_H

#include "common.h"

// Initializes PF0 (M1PWM4) at 1200 Hz — FSK mark tone (bit = 1)
void Init_PWM();

// Switches PWM frequency for FSK modulation
// 1200 Hz = mark (1), 2200 Hz = space (0)
void setPWMFrequency(uint32_t freq);

#endif