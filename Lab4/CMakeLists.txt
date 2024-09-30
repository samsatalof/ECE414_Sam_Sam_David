cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(ts_test C ASM CXX) #unit_tests

pico_sdk_init()

add_executable(ts_test #unit_tests
        ts_test.c #unit_tests.c
	TFTMaster.c
        TouchScreen.c
        ts_lcd.c
        
        )

# pull in common dependencies
target_link_libraries(ts_test pico_stdlib pico_bootsel_via_double_reset) #unit_tests

# create map/bin/hex file etc.
pico_add_extra_outputs(ts_test) #unit_tests

