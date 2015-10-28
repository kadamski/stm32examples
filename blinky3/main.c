#include <stdint.h>
#include <string.h>
#include "stm32f0xx.h"

volatile int tick_ms = 0;

void SysTick_Handler(void)
{
    tick_ms++;
}

static inline void delay(int c)
{
    volatile int end_time = tick_ms + c;

    while (tick_ms < end_time) {
        __asm volatile("wfi");
    }
}

int main(void)
{
    RCC->AHBENR |= 1<<17; // enable port A

    GPIOA->MODER |= 1<<14; // set PA7 as output

    GPIOA->OTYPER &= ~(1<<7); // ensure PA7 push-pull

    SysTick_Config(SystemCoreClock/1000-1); // 1ms tick

    for (;;)
    {
        GPIOA->BSRR = 1<<7; // set PA7
        delay(1000);

        GPIOA->BSRR = 1<<(7+16); // reset PA7
        delay(1000);
    }

    return 0;
}

// dummy function
void _init(void) {}
