#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/cm3/systick.h>
#include <libopencm3/stm32/usart.h>

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

void gpio_setup(void)
{
    rcc_periph_clock_enable(RCC_GPIOA);
    rcc_periph_clock_enable(RCC_USART1);

    gpio_mode_setup(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO7);
    gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO9);
    gpio_set_af(GPIOA, GPIO_AF1, GPIO9);
}

void uart_setup(void)
{
    usart_set_baudrate(USART1, 115200);
    usart_set_databits(USART1, 8);
    usart_set_parity(USART1, USART_PARITY_NONE);
    usart_set_stopbits(USART1, USART_CR2_STOP_1_0BIT);
    usart_set_mode(USART1, USART_MODE_TX);
    usart_set_flow_control(USART1, USART_FLOWCONTROL_NONE);

    usart_enable(USART1);
}

void systick_setup(void)
{
    systick_clear();
    systick_set_clocksource(STK_CSR_CLKSOURCE_EXT);
    systick_set_reload(1000);
    systick_interrupt_enable();
    systick_counter_enable();
}

int main(void)
{
    unsigned int i = 0;

    gpio_setup();
    uart_setup();
    systick_setup();

    while (1) {
        gpio_toggle(GPIOA, GPIO7);

        usart_send_blocking(USART1, '0' + (i++)%10);
        usart_send_blocking(USART1, '\r');
        usart_send_blocking(USART1, '\n');

        delay(1000);
    }

    return 0;
}
