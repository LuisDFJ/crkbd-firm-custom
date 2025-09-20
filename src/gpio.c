#include "gpio.h"

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
