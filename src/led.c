#include "led.h"

const uint8_t mapped_leds_back[NUM_BACK] = MAPPED_LEDS_BACK;
const uint8_t mapped_leds_keys[MATRIX_ROWS][MATRIX_COLS] = MAPPED_LEDS_KEYS;
uint32_t pixels[NUM_PIXELS];

pio_t init_pio( void ){
    pio_t p;
    bool success = pio_claim_free_sm_and_add_program_for_gpio_range(&ws2812_program, &p.pio, &p.sm, &p.offset, WS2812_PIN, 1, true);
    hard_assert(success);
    ws2812_program_init(p.pio, p.sm, p.offset, WS2812_PIN, 800000);
    return p;
}

void clear_pio( pio_t p ){
    pio_remove_program_and_unclaim_sm(&ws2812_program, p.pio, p.sm, p.offset);
}

static inline void put_pixel(PIO pio, uint sm, uint32_t pixel_grb) {
    pio_sm_put_blocking(pio, sm, pixel_grb << 8u);
}

static inline uint32_t urgb_u32(uint8_t r, uint8_t g, uint8_t b) {
    return ((uint32_t) (r) <<  8) |
           ((uint32_t) (g) << 16) |
            (uint32_t) (b);
}

void draw_matrix( pio_t p ){
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
        put_pixel(p.pio, p.sm, pixels[i]);
    }
}
