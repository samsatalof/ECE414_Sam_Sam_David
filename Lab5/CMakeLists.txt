cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)
project(calc)

pico_sdk_init()

add_executable(calc
        calc.c
        TFTMaster.c
        TouchScreen.c
        ts_lcd.c
        timer.c
	user_interface.c
)

pico_generate_pio_header(calc ${CMAKE_CURRENT_LIST_DIR}/SPIPIO.pio)

# pull in common dependencies
target_link_libraries(calc pico_stdlib pico_bootsel_via_double_reset hardware_adc hardware_timer hardware_gpio hardware_pio hardware_irq)

# create map/bin/hex file etc.
pico_add_extra_outputs(calc)
