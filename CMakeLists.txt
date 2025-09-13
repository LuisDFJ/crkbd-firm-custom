cmake_minimum_required(VERSION 3.13)

include(~/workspace/devel/pico-sdk/pico_sdk_init.cmake)

project(crkbd C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_executable(crkbd main.c)
target_link_libraries(crkbd pico_stdlib)
target_link_libraries(crkbd pico_bootsel_via_double_reset)
pico_add_extra_outputs(crkbd)
