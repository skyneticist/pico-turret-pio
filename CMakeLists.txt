# Set minimum required version of CMake
cmake_minimum_required(VERSION 3.12)

# Include build functions from Pico SDK
include(~/pico/pico-sdk/external/pico_sdk_import.cmake)

# Set name of project (as PROJECT_NAME) and C/C   standards
project(pid_mnodular C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Creates a pico-sdk subdirectory in our project for the libraries
pico_sdk_init()

# Tell CMake where to find the executable source file
add_executable(${PROJECT_NAME} 
    ${CMAKE_CURRENT_SOURCE_DIR}/main.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/core1.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/fsm.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pid_controller.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/speed_profile.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/stepper.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/uart.c
)

# Create map/bin/hex/uf2 files
pico_add_extra_outputs(${PROJECT_NAME})

# Create C header file with the name <pio program>.pio.h

# Target include directory
target_include_directories(${PROJECT_NAME}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Link to pico_stdlib (gpio, time, etc. functions)
target_link_libraries(${PROJECT_NAME} 
    pico_stdlib
    pico_multicore
    hardware_gpio
    hardware_uart
    hardware_pwm
    hardware_irq
)

# Enable usb output, disable uart output
pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 1)