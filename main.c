#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"

#include "PIN_CFG.h"
#include "led.h"
#include "scan.h"
#include "gpio.h"

void foo( void ){
    for(int i = 0; i < 5;i++){
        gpio_put(LED_PIN, 1);
        sleep_ms(250);
        gpio_put(LED_PIN, 0);
        sleep_ms(250);
    }
}

int main() {
    stdio_init_all();
    init_gpio();
    pio_t p = init_pio();

    // TODO: Use only for development.
    foo();

    while (true) {
        scan_matrix();
        draw_matrix( p );
        sleep_ms(10);

        printf("hello\n");
    }

    clear_pio(p);
}
