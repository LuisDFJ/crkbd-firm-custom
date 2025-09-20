#include "scan.h"

uint32_t scanned_register = 0x0000;

void write_scan_register( uint8_t, uint8_t, bool );

void scan_matrix( void ){
    #ifndef  SWITCH_SCAN_MODE
    for( int i = 0; i < MATRIX_ROWS; i++ ){
        gpio_put(MATRIX_SCAN_ROWS_PINS[i], 0);
        sleep_us(5);
        for( int j = 0; j < MATRIX_COLS; j++ ){
            write_scan_register( i,j,!gpio_get( MATRIX_SCAN_COLS_PINS[j] ) );
        }
        gpio_put(MATRIX_SCAN_ROWS_PINS[i], 1);
    }
    #else
    for( int j = 0; j < MATRIX_COLS; j++ ){
        gpio_put(MATRIX_SCAN_COLS_PINS[j], 1);
        sleep_us(5);
        for( int i = 0; i < MATRIX_ROWS; i++ ){
            write_scan_register( i,j,gpio_get( MATRIX_SCAN_ROWS_PINS[i] ) );
        }
        gpio_put(MATRIX_SCAN_COLS_PINS[j], 0);
    }
    #endif

}

bool read_scan_register( uint8_t r, uint8_t c ){
    uint32_t mask = 1u << ( r * MATRIX_COLS + c );
    return ( scanned_register & mask ) ? true : false;
}

void write_scan_register( uint8_t r, uint8_t c, bool val ){
    uint32_t mask = 1u << ( r * MATRIX_COLS + c );
    if(val){
        scanned_register |= mask;
    } else {
        scanned_register &= ~mask;
    }
}
