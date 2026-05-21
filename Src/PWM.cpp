#include "PWM.h"

void Init_PWM()
{
    /* Enable Peripheral Clocks */
    SYSCTL->RCGCPWM  |= (1 << 1);   /* enable clock to PWM1 */
    SYSCTL->RCGCGPIO |= (1 << 5);   /* enable clock to PORTF */
    SYSCTL->RCC &= ~0x00100000;      /* no pre-divide for PWM clock (USEPWMDIV=0) */

    /* Wait for peripherals to be ready — datasheet mandated */
    while ((SYSCTL->PRPWM  & (1 << 1)) == 0) {}   /* wait for PWM1 ready */
    while ((SYSCTL->PRGPIO & (1 << 5)) == 0) {}   /* wait for PORTF ready */

    /* Unlock PF0 — required, it's the NMI pin */
    GPIOF->LOCK = 0x4C4F434B;
    GPIOF->CR  |= (1 << 0);

    /* Configure PF0 for M1PWM4 */
    GPIOF->AFSEL |=  (1 << 0);       /* PF0 alternate function */
    GPIOF->PCTL  &= ~0x0000000F;     /* clear PMC0 */
    GPIOF->PCTL  |=  0x00000005;     /* PMC0 = 5 → M1PWM4 */
    GPIOF->DEN   |=  (1 << 0);       /* digital enable */

    /* Configure PWM1 Generator 2 for M1PWM4 (output A) */
    PWM1->_2_CTL  = 0;               /* disable generator, count down mode */
    PWM1->_2_GENA = 0x0000008C;      /* set on reload, clear on CMPA match */
    PWM1->_2_LOAD = 13333;           /* 1200 Hz = 16MHz / 13333 */
    PWM1->_2_CMPA = 6666;            /* 50% duty cycle */
    PWM1->_2_CTL  = 1;               /* enable generator */
    PWM1->ENABLE |= (1 << 4);        /* enable M1PWM4 output (bit 4) */
}

void setPWMFrequency(uint32_t freq)
{
    uint32_t load = 16000000 / freq;
    PWM1->_2_LOAD = load - 1;
    PWM1->_2_CMPA = (load / 2) - 1;
}