#pragma once

#include <stdlib.h>
#include "bsp/board.h"
#include "tusb.h"
#include "keyboard.h"

enum {
  REPORT_ID_KEYBOARD = 1,
};

enum {
    USB_NOT_MOUNTED,
    USB_MOUNTED,
    USB_SUSPENDED,
    USB_CAPSLOCK
};


uint8_t get_usb_hid_state( void );
void    set_usb_hid_state( uint8_t );

void hid_task(void);
