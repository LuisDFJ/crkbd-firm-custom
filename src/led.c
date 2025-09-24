#include "led.h"

const uint8_t mapped_leds_back[NUM_BACK] = MAPPED_LEDS_BACK;
const uint8_t mapped_leds_keys[MATRIX_ROWS][MATRIX_COLS] = MAPPED_LEDS_KEYS;
uint32_t pixels[NUM_PIXELS];

static inline uint32_t urgb_u32(uint8_t r, uint8_t g, uint8_t b) {
    return ((uint32_t) (r) <<  8) |
           ((uint32_t) (g) << 16) |
            (uint32_t) (b);
}

void draw_matrix( void ){
    for( int i = 0; i < 6; i++){
        pixels[mapped_leds_back[i]] = urgb_u32(0xFF, 0x00, 0x00);
    }
    for( int i = 0; i < MATRIX_ROWS; i++ ){
        for( int j = 0; j < MATRIX_COLS; j++ ){
            if( mapped_leds_keys[i][j] != NPIX ){
                //pixels[NUM_BACK+mapped_leds_keys[i][j]] = scanned_matrix[i][j] ? urgb_u32(0xFF, 0x00, 0x00) : urgb_u32(0x00, 0x00, 0x00); 
                pixels[NUM_BACK+mapped_leds_keys[i][j]] = read_scan_register(i, j) ? urgb_u32(0xFF, 0x00, 0x00) : urgb_u32(0x00, 0x00, 0x00); 
            }
        }
    }
    for( int i = 0; i < NUM_PIXELS; i++ ){
        put_pixel(pixels[i]);
    }
}
