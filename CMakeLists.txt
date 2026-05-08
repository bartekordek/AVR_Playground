cmake_minimum_required(VERSION 3.16)
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR avr)
set(CMAKE_CROSSCOMPILING TRUE)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
set(CMAKE_PLATFORM_HAS_INSTALLNAME FALSE)
set(CMAKE_CXX_LINK_EXECUTABLE "<CMAKE_CXX_COMPILER> <FLAGS> <CMAKE_CXX_LINK_FLAGS> <LINK_FLAGS> <OBJECTS> -o <TARGET> <LINK_LIBRARIES>")

# Toolchain (you can also move this to a toolchain file)
set(TOOLCHAIN_PATH "${CMAKE_SOURCE_DIR}/3rd_party/avr8-gnu-toolchain-win32_x86_64")
message("DEBUG: TOOLCHAIN_PATH: ${TOOLCHAIN_PATH}")
set(CMAKE_C_COMPILER   "${TOOLCHAIN_PATH}/bin/avr-gcc.exe")
set(CMAKE_CXX_COMPILER "${TOOLCHAIN_PATH}/bin/avr-g++.exe")
set(CMAKE_OBJCOPY "${TOOLCHAIN_PATH}/bin/avr-objcopy.exe")
set(CMAKE_SIZE    "${TOOLCHAIN_PATH}/bin/avr-size.exe")

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Project
project(AVR_Project C CXX)

# MCU settings
set(MCU atmega32)
set(F_CPU 16000000UL)


# Compiler flags
set(OPTIM_FLAG "-Os")
set(PRINTF_ENABLED, -Wl,-u,vfprintf -lprintf_flt)

set(CMAKE_C_FLAGS "-mmcu=${MCU} -Os -DF_CPU=16000000UL")
set(CMAKE_CXX_FLAGS "-mmcu=${MCU} -Os -DF_CPU=16000000UL -std=gnu++17 -Wall -Wextra")


add_compile_options(
    -mmcu=atmega32
    -DF_CPU=16000000UL
    -Os
    -Wall
    -Wextra
    -Wl,-u,vfprintf
    -lprintf_flt
    -fno-sized-deallocation
    # -mmcu=${MCU}
    # -DF_CPU=${F_CPU}
    # ${OPTIM_FLAG}
    # -Wall
    # -Wextra
    # ${PRINTF_ENABLED}
    # # -ffunction-sections
    # # -fdata-sections
)

add_link_options(
    -mmcu=atmega32
    -DF_CPU=16000000UL
    -Os
    -Wall
    -Wextra
    -Wl,-u,vfprintf
    -lprintf_flt
    -flto
    -fno-sized-deallocation
    # -Wl,--gc-sections
)

# Include directories
include_directories(inc)

# Sources
file(GLOB_RECURSE SOURCES src/*.cpp src/*.hpp inc/*.hpp Utils/inc/*.hpp Utils/src/*.cpp)

message("CMAKE_CXX_LINK_EXECUTABLE 00: ${CMAKE_CXX_LINK_EXECUTABLE}")
# ELF output
add_executable(main.elf ${SOURCES})

message("CMAKE_CXX_LINK_EXECUTABLE 01: ${CMAKE_CXX_LINK_EXECUTABLE}")

# HEX generation
add_custom_command(
    TARGET main.elf POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex main.elf main.hex
    COMMENT "Generating HEX file"
)

set(AVRDUDE_ROOT "${CMAKE_SOURCE_DIR}/3rd_party/avrdude")
set(AVRDUDE "${AVRDUDE_ROOT}/avrdude.exe")

# Flash target
add_custom_target(flash
    COMMAND ${AVRDUDE} -c usbasp -p ${MCU} -U flash:w:main.hex:i
    USES_TERMINAL
    DEPENDS main.elf
)
target_include_directories(main.elf PRIVATE
    ${CMAKE_SOURCE_DIR}/inc
    ${CMAKE_SOURCE_DIR}/Utils/inc
)