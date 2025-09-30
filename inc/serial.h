#pragma once

#include "pico/stdlib.h"
#include "PIN_CFG.h"
// INC RIGHT
#include "hardware/irq.h"
#include "hardware/uart.h"
// INC LEFT
#include "hardware/pio.h"
#include "pio/uart_tx.pio.h"
#include "pio/pio.h"
#include "scan.h"


#define UART_RIGHT uart0

void init_serial( void );
void serial_task( void );
uint32_t get_scan_register_left( void );
