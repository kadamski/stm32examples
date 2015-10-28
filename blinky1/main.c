#include <stdint.h>
#include "stm32f0xx.h"

static inline void delay(int c)
{
    volatile int i;

    for (i=0; i<c; i++) continue;
}

int _main(void)
{
    RCC->AHBENR |= 1<<17; // enable port A

    GPIOA->MODER |= 1<<14; // set PA7 as output

    GPIOA->OTYPER &= ~(1<<7); // ensure PA7 push-pull

    for (;;)
    {
        GPIOA->BSRR = 1<<7; // set PA7
        delay(1000000);

        GPIOA->BSRR = 1<<(7+16); // reset PA7
        delay(1000000);
    }

    return 0;
}
