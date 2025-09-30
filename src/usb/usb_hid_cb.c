#include "usb_hid.h"

uint8_t usb_hid_state = USB_NOT_MOUNTED;

uint8_t get_usb_hid_state( void ){
    return usb_hid_state;
}

void set_usb_hid_state( uint8_t state ){
    usb_hid_state = state;
}

void tud_hid_report_complete_cb(uint8_t instance, const uint8_t* report, uint16_t len) {
    (void)instance;
    (void)len;
}

uint16_t tud_hid_get_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t *buffer, uint16_t reqlen) {
    (void)instance;
    (void)report_id;
    (void)report_type;
    (void)buffer;
    (void)reqlen;
    return 0;
}

void tud_hid_set_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t const *buffer, uint16_t bufsize) {
    (void)instance;
    if (report_type == HID_REPORT_TYPE_OUTPUT && report_id == REPORT_ID_KEYBOARD ) {
        if (bufsize < 1) return;

        uint8_t const kbd_leds = buffer[0];
        if (kbd_leds & KEYBOARD_LED_CAPSLOCK) {
            usb_hid_state = USB_CAPSLOCK;
        } else {
            usb_hid_state = USB_MOUNTED;
        }
    }
}

void tud_mount_cb(void) {
    usb_hid_state = USB_MOUNTED;
}

void tud_umount_cb(void) {
    usb_hid_state = USB_NOT_MOUNTED;
}

void tud_suspend_cb(bool remote_wakeup_en) {
    (void)remote_wakeup_en;
    usb_hid_state = USB_SUSPENDED;
}

void tud_resume_cb(void) {
    usb_hid_state = USB_MOUNTED;
}
