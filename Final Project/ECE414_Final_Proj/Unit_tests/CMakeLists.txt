cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(main C ASM CXX)

pico_sdk_init()

add_executable(main
        main.c
	FSR_read.c
	timer.c
	synth_chip.c
        )

# pull in common dependencies
target_link_libraries(main pico_stdlib hardware_spi hardware_timer pico_bootsel_via_double_reset)

# create map/bin/hex file etc.
pico_add_extra_outputs(main)

