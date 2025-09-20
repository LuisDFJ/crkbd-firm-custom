#pragma once

#include "pico/stdlib.h"
#include "PIN_CFG.h"

#define SWITCH_SCAN_MODE

void scan_matrix( void );
bool read_scan_register( uint8_t r, uint8_t c );
