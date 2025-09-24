#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "PIN_CFG.h"
#include "led.h"
#include "scan.h"
#include "gpio.h"
#include "serial.h"
#include "pio.h"

void foo( void ){
    for(int i = 0; i < 5;i++){
        gpio_put(LED_PIN, 1);
        sleep_ms(250);
        gpio_put(LED_PIN, 0);
        sleep_ms(250);
    }
}

int main() {
    //stdio_init_all();
    init_gpio();
    init_pio();
    init_serial();

    // TODO: Use only for development.
    foo();

    while (true) {
        scan_matrix();
        serial_task();
        draw_matrix();
        sleep_ms(10);
    }

    clear_pio();
}







