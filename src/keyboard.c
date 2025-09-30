#include "keyboard.h"

bool keyboard_parse( uint8_t keycodes[6], uint8_t *modifier ){
    uint32_t right = get_scan_register();
    uint32_t left  = get_scan_register_left();
    if( right || left ){
        keycodes[0] = HID_KEY_A;
        keycodes[1] = HID_KEY_B;
        *modifier = left ? KEYBOARD_MODIFIER_LEFTSHIFT : 0x00;
        return true;
    }
    return false;
}
