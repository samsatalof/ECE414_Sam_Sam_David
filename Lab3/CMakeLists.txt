cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(Lab3 C ASM CXX) #unit_tests

pico_sdk_init()

add_executable(Lab3 #unit_tests
        Lab3.c #unit_tests.c
	sw_in.c
	led_out.c
        debounce_sw1.c
        debounce_sw2.c
        timer.c
        
        )

# pull in common dependencies
target_link_libraries(Lab3 pico_stdlib pico_bootsel_via_double_reset) #unit_tests

# create map/bin/hex file etc.
pico_add_extra_outputs(Lab3) #unit_tests

