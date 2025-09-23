cmake_minimum_required(VERSION 3.13)

include(~/workspace/devel/pico-sdk/pico_sdk_init.cmake)

project(crkbd C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
include_directories(inc)
include_directories(inc/usb)
add_subdirectory(src)

pico_sdk_init()


add_executable(crkbd_right)
pico_generate_pio_header(crkbd_right ${CMAKE_CURRENT_LIST_DIR}/src/ws2812.pio OUTPUT_DIR ${CMAKE_CURRENT_LIST_DIR}/inc)
pico_generate_pio_header(crkbd_right ${CMAKE_CURRENT_LIST_DIR}/src/uart_tx.pio OUTPUT_DIR ${CMAKE_CURRENT_LIST_DIR}/inc)
target_compile_definitions(crkbd_right PRIVATE "SPLIT_RIGHT")
target_link_libraries(crkbd_right pico_stdlib hardware_pio hardware_uart)
target_link_libraries(crkbd_right pico_bootsel_via_double_reset)
#target_link_libraries(crkbd_right tinyusb_device tinyusb_board)
target_link_libraries(crkbd_right src)

#pico_enable_stdio_usb(crkbd_right 1)
target_sources(crkbd_right PRIVATE main.c)

pico_add_extra_outputs(crkbd_right)



add_executable(crkbd_left)
pico_generate_pio_header(crkbd_left ${CMAKE_CURRENT_LIST_DIR}/src/ws2812.pio OUTPUT_DIR ${CMAKE_CURRENT_LIST_DIR}/inc)
pico_generate_pio_header(crkbd_left ${CMAKE_CURRENT_LIST_DIR}/src/uart_tx.pio OUTPUT_DIR ${CMAKE_CURRENT_LIST_DIR}/inc)
target_compile_definitions(crkbd_left PRIVATE "SPLIT_LEFT")
target_link_libraries(crkbd_left pico_stdlib hardware_pio)
target_link_libraries(crkbd_left pico_bootsel_via_double_reset)
#target_link_libraries(crkbd_left tinyusb_device tinyusb_board)
target_link_libraries(crkbd_left src)

#pico_enable_stdio_usb(crkbd_left 1)
target_sources(crkbd_left PRIVATE main.c)

pico_add_extra_outputs(crkbd_left)
