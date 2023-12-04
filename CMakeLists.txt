cmake_minimum_required(VERSION 3.15)


##### BASE PROJECT CONFIG
# specify cross-compilers and tools
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)
set(CMAKE_AR arm-none-eabi-ar)
set(CMAKE_OBJCOPY arm-none-eabi-objcopy)
set(CMAKE_OBJDUMP arm-none-eabi-objdump)
set(SIZE arm-none-eabi-size)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)


project(obc)

file(GLOB_RECURSE SOURCES "Core/*.*" "Drivers/*.*" )

add_executable(${PROJECT_NAME}.elf ${SOURCES} ${LINKER_SCRIPT})


set(HEX_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.hex)
set(BIN_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.bin)

target_link_libraries(${PROJECT_NAME}.elf freertos_kernel freertos_config)

# Linker

set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/STM32F411RETX_FLASH.ld)
add_link_options(-Wl,-gc-sections,--print-memory-usage,-Map=${PROJECT_BINARY_DIR}/${PROJECT_NAME}.map)
add_link_options(-mcpu=cortex-m4 -mthumb -mthumb-interwork)
add_link_options(-T ${LINKER_SCRIPT})


##### FREERTOS

set(FREERTOS_KERNEL_PATH "Middlewares/Third_Party/FreeRTOS-Kernel")

# Add the freertos_config for FreeRTOS-Kernel
add_library(freertos_config INTERFACE)

target_include_directories(freertos_config
        INTERFACE
        Core/Inc
)

# Select the heap port.  values between 1-4 will pick a heap.
set(FREERTOS_HEAP "4" CACHE STRING "" FORCE)

# Select the native compile PORT
set(FREERTOS_PORT "TEMPLATE" CACHE STRING "" FORCE)

# Adding the FreeRTOS-Kernel subdirectory
add_subdirectory(${FREERTOS_KERNEL_PATH} FreeRTOS-Kernel)

########################################################################
# Overall Compile Options
# Note the compile option strategy is to error on everything and then
# Per library opt-out of things that are warnings/errors.
# This ensures that no matter what strategy for compilation you take, the
# builds will still occur.
#
# Only tested with GNU and Clang.
# Other options are https://cmake.org/cmake/help/latest/variable/CMAKE_LANG_COMPILER_ID.html#variable:CMAKE_%3CLANG%3E_COMPILER_ID
# Naming of compilers translation map:
#
#   FreeRTOS    | CMake
#   -------------------
#   CCS         | ?TBD?
#   GCC         | GNU, Clang, *Clang Others?
#   IAR         | IAR
#   Keil        | ARMCC
#   MSVC        | MSVC # Note only for MinGW?
#   Renesas     | ?TBD?

target_compile_options(freertos_kernel PRIVATE
        ### Gnu/Clang C Options
        $<$<COMPILE_LANG_AND_ID:C,GNU>:-fdiagnostics-color=always>
        $<$<COMPILE_LANG_AND_ID:C,Clang>:-fcolor-diagnostics>

        $<$<COMPILE_LANG_AND_ID:C,Clang,GNU>:-Wall>
        $<$<COMPILE_LANG_AND_ID:C,Clang,GNU>:-Wextra>
        $<$<COMPILE_LANG_AND_ID:C,Clang,GNU>:-Wpedantic>
        $<$<COMPILE_LANG_AND_ID:C,Clang,GNU>:-Werror>
        $<$<COMPILE_LANG_AND_ID:C,Clang,GNU>:-Wconversion>
        $<$<COMPILE_LANG_AND_ID:C,Clang>:-Weverything>

        # Suppressions required to build clean with clang.
        $<$<COMPILE_LANG_AND_ID:C,Clang>:-Wno-unused-macros>
        $<$<COMPILE_LANG_AND_ID:C,Clang>:-Wno-padded>
        $<$<COMPILE_LANG_AND_ID:C,Clang>:-Wno-missing-variable-declarations>
        $<$<COMPILE_LANG_AND_ID:C,Clang>:-Wno-covered-switch-default>
        $<$<COMPILE_LANG_AND_ID:C,Clang>:-Wno-cast-align> )



##### FAT

set(FREERTOS_FAT_PATH "Middlewares/Third_Party/Lab-Project-FreeRTOS-FAT")


set( FREERTOS_PLUS_FAT_DEV_SUPPORT OFF CACHE BOOL "" FORCE)
# Select the native compile PORT
set( FREERTOS_PLUS_FAT_PORT "POSIX" CACHE STRING "" FORCE)
# Select the cross-compile PORT
if (CMAKE_CROSSCOMPILING)
    # Eg. Zynq 2019_3 version of port
    set(FREERTOS_PLUS_FAT_PORT "ZYNQ_2019_3" CACHE STRING "" FORCE)
endif()


# Including FAT make the compilation really long
#add_subdirectory(${FREERTOS_FAT_PATH} FreeRTOS-FAT)
