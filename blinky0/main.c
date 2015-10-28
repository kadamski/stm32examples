#include <stdint.h>

/* RM0360 2.2.2 */
#define PERIPH_BASE         ((uint32_t)0x40000000)
#define AHB1PERIPH_BASE     (PERIPH_BASE + 0x00020000)
#define AHB2PERIPH_BASE     (PERIPH_BASE + 0x08000000)
#define RCC_BASE            (AHB1PERIPH_BASE + 0x00001000)
#define GPIOA_BASE          (AHB2PERIPH_BASE + 0x00000000)

/* RM0360 7.4.15 */
#define RCC_AHBENR          (*((volatile uint32_t*)(RCC_BASE+0x14)))

/* RM0360 8.4.12 */
#define GPIOA_MODER         (*((volatile uint32_t*)(GPIOA_BASE+0x00)))
#define GPIOA_OTYPER        (*((volatile uint32_t*)(GPIOA_BASE+0x04)))
#define GPIOA_BSRR          (*((volatile uint32_t*)(GPIOA_BASE+0x18)))

static inline void delay(int c)
{
    volatile int i;

    for (i=0; i<c; i++) continue;
}

int _main(void)
{
    RCC_AHBENR |= 1<<17; // enable port A

    GPIOA_MODER |= 1<<14; // set PA7 as output

    GPIOA_OTYPER &= ~(1<<7); // ensure PA7 push-pull

    for (;;)
    {
        GPIOA_BSRR = 1<<7; // set PA7
        delay(1000000);

        GPIOA_BSRR = 1<<(7+16); // reset PA7
        delay(1000000);
    }

    return 0;
}
