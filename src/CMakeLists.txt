add_library(src
    gpio.c
    led.c
    scan.c
)

target_link_libraries(src pico_stdlib hardware_pio)
target_include_directories(src PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
)
