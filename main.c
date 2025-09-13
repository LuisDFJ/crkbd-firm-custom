#include "pico/stdlib.h"
#include "hardware/watchdog.h"
#include "pico/bootrom.h"

#define LED_PIN 17
#define OUT_PIN 29
#define IN_PIN 6

int main() {
    gpio_init(LED_PIN);
    gpio_init(OUT_PIN);
    gpio_init(IN_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    gpio_set_dir(OUT_PIN, GPIO_OUT);
    gpio_set_dir(IN_PIN, GPIO_IN);

    gpio_put( OUT_PIN, 1 );

    while (true) {

        gpio_put(LED_PIN, 1);
        sleep_ms(250);
        gpio_put(LED_PIN, 0);
        sleep_ms(250);

        //if( gpio_get(IN_PIN) ){
            //gpio_put( LED_PIN, 1 );
        //} else {
            //gpio_put( LED_PIN, 0 );
        //}
    }
}
