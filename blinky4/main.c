#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/cm3/systick.h>

volatile int tick_ms = 0;

void sys_tick_handler(void)
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
    rcc_periph_clock_enable(RCC_GPIOA);
    gpio_mode_setup(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO7);

    systick_clear();
    systick_set_clocksource(STK_CSR_CLKSOURCE_EXT);
    systick_set_reload(1000);
    systick_interrupt_enable();
    systick_counter_enable();

    while (1) {
        gpio_toggle(GPIOA, GPIO7);
        delay(1000);
    }

    return 0;
}
