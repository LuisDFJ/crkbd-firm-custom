#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "ws2812.pio.h"

#include "PIN_CFG.h"

#define NUM_PIXELS 27
#define WS2812_PIN 0

static inline void put_pixel(PIO pio, uint sm, uint32_t pixel_grb) {
    pio_sm_put_blocking(pio, sm, pixel_grb << 8u);
}

static inline uint32_t urgb_u32(uint8_t r, uint8_t g, uint8_t b) {
    return ((uint32_t) (r) <<  8) |
           ((uint32_t) (g) << 16) |
            (uint32_t) (b);
}

void init_gpio( void ){
    gpio_init( LED_PIN );
    gpio_set_dir(LED_PIN, GPIO_OUT);
    for( int i = 0; i < MATRIX_COLS; i++ ){
        uint pin = MATRIX_SCAN_COLS_PINS[i];
        gpio_init(pin);
        //gpio_set_dir(pin, GPIO_IN);
        //gpio_pull_up(pin);
        gpio_set_dir(pin, GPIO_OUT);
        gpio_put(pin, 0);
    }
    for( int i = 0; i < MATRIX_ROWS; i++ ){
        uint pin = MATRIX_SCAN_ROWS_PINS[i];
        gpio_init(pin);
        //gpio_set_dir(pin, GPIO_OUT);
        //gpio_put(pin,1);
        gpio_set_dir(pin, GPIO_IN);
        gpio_pull_down(pin);
    }
}

uint8_t scanned_matrix[MATRIX_ROWS][MATRIX_COLS];

void scan_matrix( void ){
    //for( int i = 0; i < MATRIX_ROWS; i++ ){
        //gpio_put(MATRIX_SCAN_ROWS_PINS[i], 0);
        //sleep_us(5);
        //for( int j = 0; j < MATRIX_COLS; j++ ){
            //scanned_matrix[i][j] = !gpio_get( MATRIX_SCAN_COLS_PINS[j] );
        //}
        //gpio_put(MATRIX_SCAN_ROWS_PINS[i], 1);
    //}
    for( int j = 0; j < MATRIX_COLS; j++ ){
        gpio_put(MATRIX_SCAN_COLS_PINS[j], 1);
        sleep_us(5);
        for( int i = 0; i < MATRIX_ROWS; i++ ){
            scanned_matrix[i][j] = gpio_get( MATRIX_SCAN_ROWS_PINS[i] );
        }
        gpio_put(MATRIX_SCAN_COLS_PINS[j], 0);
    }

}

const uint8_t NPIX = 0xFF;
uint8_t mapped_matrix[MATRIX_ROWS][MATRIX_COLS] = {
    {   3,   4,  11,  12,  17,  18},
    {   2,   5,  10,  13,  16,  19},
    {   1,   6,   9,  14,  15,  20},
    {   0,   7,   8,NPIX,NPIX,NPIX},
};

uint32_t pixels[NUM_PIXELS];

void draw_matrix( void ){
    for( int i = 0; i < 6; i++){
        pixels[i] = urgb_u32(0xFF, 0x00, 0x00);
    }
    for( int i = 0; i < MATRIX_ROWS; i++ ){
        for( int j = 0; j < MATRIX_COLS; j++ ){
            if( mapped_matrix[i][j] != NPIX ){
                pixels[6+mapped_matrix[i][j]] = ( scanned_matrix[i][j] ) ? urgb_u32(0xFF, 0x00, 0x00) : urgb_u32(0x00, 0x00, 0x00); 
            }
        }
    }
}

int main() {
    init_gpio();

    PIO pio;
    uint sm;
    uint offset;

    bool success = pio_claim_free_sm_and_add_program_for_gpio_range(&ws2812_program, &pio, &sm, &offset, WS2812_PIN, 1, true);
    hard_assert(success);

    ws2812_program_init(pio, sm, offset, WS2812_PIN, 800000);

    for(int i = 0; i < 5;i++){
        gpio_put(LED_PIN, 1);
        for(int j = 0; j < NUM_PIXELS; j++){
            put_pixel(pio, sm, urgb_u32(0x00, 0x00, 0x00));
        }
        sleep_ms(250);
        gpio_put(LED_PIN, 0);
        for(int j = 0; j < NUM_PIXELS; j++){
            put_pixel(pio, sm, urgb_u32(0x00, 0xFF, 0x00));
        }
        sleep_ms(250);
    }

    while (true) {


        scan_matrix();
        draw_matrix();
        for(int i = 0; i < NUM_PIXELS; i++){
            put_pixel(pio, sm, pixels[i]);
        }
        sleep_ms(10);

    }

    pio_remove_program_and_unclaim_sm(&ws2812_program, pio, sm, offset);
}
