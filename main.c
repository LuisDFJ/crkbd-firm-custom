#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "bsp/board.h"
#include "PIN_CFG.h"
#include "led.h"
#include "scan.h"
#include "gpio.h"
#include "serial.h"
#include "pio.h"
#include "usb_hid.h"

void foo( void ){
    for(int i = 0; i < 5;i++){
        gpio_put(LED_PIN, 1);
        sleep_ms(250);
        gpio_put(LED_PIN, 0);
        sleep_ms(250);
    }
}

int main() {
    init_gpio();
    init_pio();
    init_serial();
    tusb_init();

    // TODO: Use only for development.
    foo();

    uint32_t t = 0;
    while (true) {
        tud_task();
        if( board_millis() - t > 10 ){
            t = board_millis();
            scan_matrix();
            serial_task();
            draw_matrix();
            hid_task();
            //sleep_ms(10);
        }
    }

    clear_pio();
}
