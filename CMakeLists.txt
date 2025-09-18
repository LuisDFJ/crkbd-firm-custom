cmake_minimum_required(VERSION 3.13)

include(~/workspace/devel/pico-sdk/pico_sdk_init.cmake)

project(crkbd C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
include_directories(inc)

pico_sdk_init()

add_executable(crkbd)
target_link_libraries(crkbd pico_stdlib hardware_pio)
target_link_libraries(crkbd pico_bootsel_via_double_reset)

pico_generate_pio_header(crkbd ${CMAKE_CURRENT_LIST_DIR}/ws2812.pio OUTPUT_DIR ${CMAKE_CURRENT_LIST_DIR}/inc)

target_sources(crkbd PRIVATE main.c)

pico_add_extra_outputs(crkbd)
