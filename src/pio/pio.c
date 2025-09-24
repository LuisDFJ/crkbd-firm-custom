#include "pio/pio.h"

pio_t p[2];

pio_t init_pio_led( void ){
    pio_t p;
    bool success = pio_claim_free_sm_and_add_program_for_gpio_range(&ws2812_program, &p.pio, &p.sm, &p.offset, WS2812_PIN, 1, true);
    hard_assert(success);
    ws2812_program_init(p.pio, p.sm, p.offset, WS2812_PIN, 800000);
    return p;
}

pio_t init_pio_tx( void ){
    pio_t p;
    bool success = pio_claim_free_sm_and_add_program_for_gpio_range(&uart_tx_program, &p.pio, &p.sm, &p.offset, TRRS_PIN, 1, true);
    hard_assert(success);
    uart_tx_program_init(p.pio, p.sm, p.offset, TRRS_PIN, BAUD_RATE);
    return p;
}

void init_pio( void ){
    p[0] = init_pio_led();
#ifdef SPLIT_LEFT
    p[1] = init_pio_tx();
#endif
}

void clear_pio( void ){
    pio_remove_program_and_unclaim_sm(&ws2812_program, p[0].pio, p[0].sm, p[0].offset);
#ifdef SPLIT_LEFT
    pio_remove_program_and_unclaim_sm(&uart_tx_program, p[1].pio, p[1].sm, p[1].offset);
#endif
}


void put_pixel( uint32_t pixel_grb) {
    pio_sm_put_blocking(p[0].pio, p[0].sm, pixel_grb << 8u);
}

void uart_tx_reg(  uint32_t reg ){
    uint8_t *c = (uint8_t*)&reg;
    for( int i = 0; i < 4; i++){
        uart_tx_program_putc(p[1].pio, p[1].sm, c[i]);
    }
}

