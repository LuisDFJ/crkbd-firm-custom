#include "usb_hid.h"

uint8_t keycodes[6];
uint8_t modifier;

static void send_hid_report(bool pressed) {
    if ( !tud_hid_ready() ) return;

    static bool send_empty = false;

    if (pressed) {
        tud_hid_keyboard_report(REPORT_ID_KEYBOARD, modifier, keycodes);
        send_empty = true;
    } else {
        if (send_empty) {
            tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, NULL);
        }
        send_empty = false;
    }
}

void hid_task(void) {
#ifdef SPLIT_RIGHT
    bool pressed = keyboard_parse( keycodes, &modifier );
    if (tud_suspended() && pressed) {
        tud_remote_wakeup();
    } else {
        send_hid_report(pressed);
    }
#endif
}











