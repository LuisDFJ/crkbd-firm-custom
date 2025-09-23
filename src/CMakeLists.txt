add_library(src
    gpio.c
    led.c
    scan.c
    usb/usb_descriptors.c
)

target_link_libraries(src pico_stdlib hardware_pio)
target_link_libraries(src tinyusb_device tinyusb_board)
target_include_directories(src PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../inc
)
target_include_directories(src PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../inc/usb
)
