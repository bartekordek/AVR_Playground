# CMakeLists.txt for AtemagaUtils static library
cmake_minimum_required(VERSION 3.15)

project(AvrUtils LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

# Set the source and header files
file(GLOB_RECURSE ATEMAGAUTILS_SRC
    "src/*.cpp"
)
file(GLOB_RECURSE ATEMAGAUTILS_HEADERS
    "inc/*.hpp"
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
    # -Wl,--gc-sections
)

# Create the static library
add_library(AvrUtils STATIC ${ATEMAGAUTILS_SRC} ${ATEMAGAUTILS_HEADERS})

# Set the include directories for consumers
# (PUBLIC so consumers get the headers)
target_include_directories(AvrUtils PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc>
    $<INSTALL_INTERFACE:inc>
)
