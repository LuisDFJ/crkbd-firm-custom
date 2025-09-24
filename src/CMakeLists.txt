add_library(crkbd_src_left
    gpio.c
    led.c
    scan.c
    serial.c
    usb/usb_descriptors.c
    pio/pio.c
)

target_compile_definitions(crkbd_src_left PRIVATE "SPLIT_LEFT")
target_link_libraries(crkbd_src_left pico_stdlib hardware_pio)
target_link_libraries(crkbd_src_left tinyusb_device tinyusb_board)

add_library(crkbd_src_right
    gpio.c
    led.c
    scan.c
    serial.c
    usb/usb_descriptors.c
    pio/pio.c
)

target_compile_definitions(crkbd_src_right PRIVATE "SPLIT_RIGHT")
target_link_libraries(crkbd_src_right pico_stdlib hardware_pio)
target_link_libraries(crkbd_src_right tinyusb_device tinyusb_board)
