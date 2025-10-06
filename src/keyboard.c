#include "keyboard.h"
#include "keymap/keymap.h"

void get_pressed( uint32_t l_reg, uint32_t r_reg, uint8_t keycodes[6], uint8_t *modifier );

bool keyboard_parse( uint8_t keycodes[6], uint8_t *modifier ){
    uint32_t right = get_scan_register();
    uint32_t left  = get_scan_register_left();

    *modifier = 0x00;
    for (int i = 0; i < 6; i++) keycodes[i] = 0x00;

    if( right || left ){
        get_pressed( left, right, keycodes, modifier );
        return true;
    }
    return false;
}

typedef struct {
    uint8_t layer;
    uint8_t modifier;
    uint8_t keycode;
} KCP_t;

uint8_t get_keycode( int i, int layer, const bool is_right ){
    int r = i / MATRIX_COLS;
    int c = i % MATRIX_COLS;
    return keymaps[ layer ][ is_right ][ r ][ c ];
}

KCP_t parse_keycode( const int i, const int layer, const bool is_right ){
    uint8_t keycode = get_keycode(i, layer, is_right); 
    KCP_t res = { .keycode = XXXXXXX };
    switch (keycode) {
        case _______:
            res = parse_keycode(i, 0, is_right);
            break;
        case BASIC_KC_RANGE:
        case SYSTEM_KC_RANGE:
            res.keycode = keycode;
            break;
        case MODIFIER_KC_RANGE:
            res.modifier = MODIFIER_CODE( keycode );
            break;
        case LAYER_KC_RANGE:
            res.layer = LAYER_NUM( keycode );
            break;
        case XXXXXXX:
        default:
            break;
    }
    return res;
}

void get_layer_wrap( int *layer, uint32_t reg, const bool is_right ){
    while (reg) {
        int i = __builtin_ctz( reg );
        reg &= reg - 1;
        uint8_t keycode = get_keycode(i, *layer, is_right);
        if( IS_LAYER_KC(keycode) ){
            *layer = LAYER_NUM(keycode);
        }
    }
}

int get_layer( uint32_t l_reg, uint32_t r_reg ){
    int layer = 0;
    get_layer_wrap(&layer, l_reg, false);
    get_layer_wrap(&layer, r_reg, true);
    return layer;
}


void get_pressed_wrap( int *c, uint32_t reg, uint8_t keycodes[6], uint8_t *modifier, const int layer, const bool is_right ){
    while ( reg && *c < 6 ) {
        int i = __builtin_ctz( reg );
        reg &= reg - 1;
        KCP_t res = parse_keycode(i, layer, is_right);
        if( res.modifier ) *modifier |= res.modifier;
        if( res.keycode ) keycodes[ (*c)++ ] = res.keycode;
    }
}

void get_pressed( uint32_t l_reg, uint32_t r_reg, uint8_t keycodes[6], uint8_t *modifier ){
    const int layer = get_layer(l_reg, r_reg);
    int c = 0;
    get_pressed_wrap(&c, l_reg, keycodes, modifier, layer, false);
    get_pressed_wrap(&c, r_reg, keycodes, modifier, layer, true);
}
