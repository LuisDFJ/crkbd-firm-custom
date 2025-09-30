#include "serial.h"

uint32_t scanned_register_left = 0x0000;

uint32_t get_scan_register_left( void ){
    return scanned_register_left;
}

void uart_rx_irq() {
    uint8_t reg[4] = {0,0,0,0};
    for( int i = 0; i < 4; i++ ){
        if( uart_is_readable( UART_RIGHT ) ){
            reg[i] = uart_getc( UART_RIGHT );
        }
    }
    uint32_t *p = ( uint32_t* ) reg;
    scanned_register_left = *p;
}

void uart_right_init() {
    uart_init(UART_RIGHT, BAUD_RATE);
    gpio_set_function(TRRS_PIN, UART_FUNCSEL_NUM(UART_RIGHT, UART_RX_PIN));
    uart_set_format(UART_RIGHT, 8, 1, UART_PARITY_NONE);
    irq_set_exclusive_handler(UART0_IRQ, uart_rx_irq);
    irq_set_enabled(UART0_IRQ, true);
    uart_set_irq_enables(UART_RIGHT, true, false);
}

void init_serial( void ){
#ifdef SPLIT_RIGHT
    uart_right_init();
#endif
}

void serial_task( void ){
#ifdef SPLIT_LEFT
    uart_tx_reg( get_scan_register() );
#endif
//#ifdef SPLIT_RIGHT
//    set_scan_register(scanned_register_left | get_scan_register());
//#endif
}

