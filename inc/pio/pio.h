#pragma once

#include "hardware/pio.h"
#include "pio/ws2812.pio.h"
#include "pio/uart_tx.pio.h"
#include "PIN_CFG.h"

typedef struct {
    PIO pio;
    uint sm;
    uint offset;
}pio_t;

void init_pio  ( void );
void clear_pio ( void );

void put_pixel( uint32_t );
void uart_tx_reg(  uint32_t );
