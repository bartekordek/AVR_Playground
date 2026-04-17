cmake_minimum_required(VERSION 3.16)

# Project
project(AVR_Project C)

# MCU settings
set(MCU atmega32)
set(F_CPU 16000000UL)

# Toolchain (you can also move this to a toolchain file)
set(CMAKE_C_COMPILER avr-gcc)
set(CMAKE_OBJCOPY avr-objcopy)

# Compiler flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mmcu=${MCU} -DF_CPU=${F_CPU} -Os -Wall -Wextra -std=c11")

# Include directories
include_directories(inc)

# Sources
set(SOURCES
    src/main.c
    src/util.c
)

# ELF output
add_executable(main.elf ${SOURCES})

# HEX generation
add_custom_command(
    TARGET main.elf POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex main.elf main.hex
    COMMENT "Generating HEX file"
)

# Flash target
add_custom_target(flash
    COMMAND avrdude -c usbasp -p ${MCU} -U flash:w:main.hex:i
    DEPENDS main.elf
    COMMENT "Flashing to MCU"
)