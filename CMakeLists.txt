cmake_minimum_required(VERSION 3.25)
project(NumericalMath C)

SET(TARGET_ARCHITECTURE "x86" CACHE STRING "CM4")
message("TARGET_ARCHITECTURE=${TARGET_ARCHITECTURE}")

if(${TARGET_ARCHITECTURE} STREQUAL "x86")

elseif(${TARGET_ARCHITECTURE} STREQUAL "CM4")
    set(CMAKE_SYSTEM_NAME Generic)
    set(CMAKE_SYSTEM_VERSION 1)

    set(CMAKE_C_STANDARD 11)

    # Setup arm processor and gcc toolchain
    set(CMAKE_SYSTEM_PROCESSOR arm)
    set(CMAKE_C_COMPILER arm-none-eabi-gcc)
    set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
    set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)
    set(CMAKE_AR arm-none-eabi-ar)
    set(CMAKE_OBJCOPY arm-none-eabi-objcopy)
    set(CMAKE_OBJDUMP arm-none-eabi-objdump)
    set(CMAKE_NM arm-none-eabi-nm)
    set(CMAKE_STRIP arm-none-eabi-strip)
    set(CMAKE_RANLIB arm-none-eabi-ranlib)
    # When trying to link cross compiled test program, error occurs, so setting test compilation to static library
    set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

    #Uncomment for hardware floating point
    add_compile_definitions(ARM_MATH_CM4;ARM_MATH_MATRIX_CHECK;ARM_MATH_ROUNDING)
    add_compile_options(-mfloat-abi=hard -mfpu=fpv4-sp-d16)
    add_link_options(-mfloat-abi=hard -mfpu=fpv4-sp-d16)

    #Uncomment for software floating point
    #add_compile_options(-mfloat-abi=soft)

    add_compile_options(-mcpu=cortex-m4 -mthumb -mthumb-interwork)
    add_compile_options(-ffunction-sections -fdata-sections -fno-common -fmessage-length=0)

    # uncomment to mitigate c++17 absolute addresses warnings
    #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-register")

    # Enable assembler files preprocessing
    add_compile_options($<$<COMPILE_LANGUAGE:ASM>:-x$<SEMICOLON>assembler-with-cpp>)

    add_compile_options(-Ofast)

    set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/STM32F401RETX_FLASH.ld)

    add_link_options(-Wl,-gc-sections,--print-memory-usage,-Map=${PROJECT_BINARY_DIR}/${PROJECT_NAME}.map)
    add_link_options(-mcpu=cortex-m4 -mthumb -mthumb-interwork)
    add_link_options(-T ${LINKER_SCRIPT})
endif()

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib")
enable_testing()
add_subdirectory(tests)

include_directories(include src)
file(GLOB_RECURSE SOURCES src/*.c)

if(${TARGET_ARCHITECTURE} STREQUAL "x86")
    add_library(NumericalMath_x86 ${SOURCES})
    add_executable(Numericalmath main.c ${SOURCES})
elseif(${TARGET_ARCHITECTURE} STREQUAL "CM4")
    add_library(NumericalMath_CM4 ${SOURCES})
endif()


