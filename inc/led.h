#pragma once

#include "pio/ws2812.pio.h"
#include "pio/pio.h"
#include "PIN_CFG.h"
#include "scan.h"

#define NUM_PIXELS  27
#define NPIX        0xFF
#define NUM_BACK    6

#define MAPPED_LEDS_BACK {\
    0,  1,  2,            \
    3,  4,  5,            \
}
#define MAPPED_LEDS_KEYS {          \
    {   3,   4,  11,  12,  17,  18},\
    {   2,   5,  10,  13,  16,  19},\
    {   1,   6,   9,  14,  15,  20},\
    {   0,   7,   8,NPIX,NPIX,NPIX},\
}

extern const uint8_t mapped_leds_back[NUM_BACK];
extern const uint8_t mapped_leds_keys[MATRIX_ROWS][MATRIX_COLS];
extern uint32_t pixels[NUM_PIXELS];

void  draw_matrix ( void );
