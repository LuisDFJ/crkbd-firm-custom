#include "keyboard.h"
#include "keymap/keymap.h"

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

uint8_t get_keycode_left( int i, int l ){
     
    keymaps[l][0][]

}

int get_layer( uint32_t l_reg, uint32_t r_reg ){
    int layer = 0;
    while( l_reg ){
        int i = __builtin_ctz( l_reg );
        l_reg &= l_reg - 1;
        if( IS_LAYER_KC(  ) )

    }

    return layer;
}

void get_pressed( uint32_t l_reg, uint32_t r_reg, uint8_t keycodes[6] ){
    int c = 0;
    int layer
    while( l_reg && c < 6 ){
        keycodes[c++] = keymap_parse_left( i );


    }
}
