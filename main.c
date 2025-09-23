#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"


#ifdef SPLIT_RIGHT
#include "hardware/irq.h"
#include "hardware/uart.h"
#endif
#ifdef SPLIT_LEFT
#include "hardware/pio.h"
#include "uart_tx.pio.h"
#endif

#include "PIN_CFG.h"
#include "led.h"
#include "scan.h"
#include "gpio.h"

#define BAUD_RATE 115200

#ifdef SPLIT_RIGHT

#define UART_RIGHT uart0
uint32_t left_keys = 0x0000;

void uart_rx_irq() {
    uint8_t reg[4] = {0,0,0,0};
    for( int i = 0; i < 4; i++ ){
        if( uart_is_readable( UART_RIGHT ) ){
            reg[i] = uart_getc( UART_RIGHT );
        }
    }
    uint32_t *p = ( uint32_t* ) reg;
    left_keys = *p;
}


void uart_right_init() {
    uart_init(UART_RIGHT, BAUD_RATE);
    //gpio_set_function(0, UART_FUNCSEL_NUM(UART_RIGHT, UART_TX_PIN));
    gpio_set_function(TRRS_PIN, UART_FUNCSEL_NUM(UART_RIGHT, UART_RX_PIN));

    uart_set_format(UART_RIGHT, 8, 1, UART_PARITY_NONE);

    irq_set_exclusive_handler(UART0_IRQ, uart_rx_irq);
    irq_set_enabled(UART0_IRQ, true);
    uart_set_irq_enables(UART_RIGHT, true, false);
}
#endif

#ifdef SPLIT_LEFT

void uart_tx_task( pio_t p, uint32_t reg ){
    uint8_t *c = (uint8_t*)&reg;
    for( int i = 0; i < 4; i++){
        uart_tx_program_putc(p.pio, p.sm, c[i]);
    }
}

pio_t uart_left_init() {
    pio_t p;
    bool success = pio_claim_free_sm_and_add_program_for_gpio_range(&uart_tx_program, &p.pio, &p.sm, &p.offset, TRRS_PIN, 1, true);
    hard_assert(success);
    uart_tx_program_init(p.pio, p.sm, p.offset, TRRS_PIN, BAUD_RATE);
    return p;
}

void uart_left_clear( pio_t p ){
    pio_remove_program_and_unclaim_sm(&uart_tx_program, p.pio, p.sm, p.offset);
}
#endif

void foo( void ){
    for(int i = 0; i < 5;i++){
        gpio_put(LED_PIN, 1);
        sleep_ms(250);
        gpio_put(LED_PIN, 0);
        sleep_ms(250);
    }
}

int main() {
    //stdio_init_all();
    init_gpio();
    pio_t p = init_pio();

#ifdef SPLIT_RIGHT
    uart_right_init();
#endif

#ifdef SPLIT_LEFT
    pio_t g = uart_left_init();
#endif


    // TODO: Use only for development.
    foo();

    while (true) {
        scan_matrix();
#ifdef SPLIT_RIGHT
        set_scan_register(left_keys | get_scan_register());
#endif

#ifdef SPLIT_LEFT
        uart_tx_task(g, get_scan_register());
#endif

        draw_matrix( p );
        sleep_ms(10);

        //printf("hello\n");
    }

    clear_pio(p);
#ifdef SPLIT_LEFT
    uart_left_clear(g);
#endif
}







