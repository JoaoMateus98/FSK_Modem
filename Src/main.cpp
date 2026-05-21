#include "TM4C123GH6PM.h"

void Init_PWM();
void setPWMFrequency(uint32_t freq);

int main(void)
{
    Init_PWM();

    setPWMFrequency(2200);
    while (true)
    {
    }
    
}