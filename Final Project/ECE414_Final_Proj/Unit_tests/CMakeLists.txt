cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(unit_tests C ASM CXX)

pico_sdk_init()

add_executable(unit_tests
        unit_tests.c
	FSR_read.c
	timer.c
	synth_chip.c
        )

# pull in common dependencies
target_link_libraries(unit_tests pico_stdlib hardware_spi hardware_timer pico_bootsel_via_double_reset)

# create map/bin/hex file etc.
pico_add_extra_outputs(unit_tests)

