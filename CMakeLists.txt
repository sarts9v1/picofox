cmake_minimum_required(VERSION 3.13)

set(NAME picofox)

include(pico_sdk_import.cmake)

project(picofox C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/morse.cpp
    src/piodco/piodco.c
)

pico_generate_pio_header(${PROJECT_NAME} ${CMAKE_CURRENT_LIST_DIR}/src/piodco/dco2.pio)

target_link_libraries(${PROJECT_NAME}
    pico_stdlib
    pico_multicore
    hardware_clocks
    hardware_pio)

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra)


pico_add_extra_outputs(${PROJECT_NAME})

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.uf2
    ${CMAKE_CURRENT_LIST_DIR}/README.md
    DESTINATION .
)
