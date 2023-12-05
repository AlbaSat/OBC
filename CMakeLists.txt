cmake_minimum_required(VERSION 3.15)
include(FetchContent)

set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)
set(CMAKE_AR arm-none-eabi-ar)
set(CMAKE_OBJCOPY arm-none-eabi-objcopy)
set(CMAKE_OBJDUMP arm-none-eabi-objdump)
set(SIZE arm-none-eabi-size)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)


# project settings
project(OBC C CXX ASM)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)

########################################################################################################################
#################################################FreeRTOS###############################################################

# Link: https://github.com/FreeRTOS/FreeRTOS-Kernel
FetchContent_Declare( freertos_kernel
        GIT_REPOSITORY https://github.com/FreeRTOS/FreeRTOS-Kernel.git
        GIT_TAG        main #Note: Best practice to use specific git-hash or tagged version
)

add_library(freertos_config INTERFACE)

target_include_directories(freertos_config SYSTEM
        INTERFACE
        Core/Inc
)

target_compile_definitions(freertos_config
        INTERFACE
        projCOVERAGE_TEST=0
)

set( FREERTOS_HEAP "4" CACHE STRING "" FORCE)
# Select the native compile PORT
#set( FREERTOS_PORT "GCC_POSIX" CACHE STRING "" FORCE)

# If we set FREERTOS_PORT to GCC_POSIX, make throws an error about PTHREAD_ONCE_INIT
# If we don't set it, make throws and error about some weird conversion from `long unsigned in` to `UBaseType_t` (`unsigned char`)
# If we set it to GCC_ARM_CM4F it complains about some lacking registers in ARM mode
set(FREERTOS_PORT "GCC_POSIX" CACHE STRING "" FORCE)

# Select the cross-compile PORT
if (CMAKE_CROSSCOMPILING)
    set(FREERTOS_PORT "GCC_ARM_CM4F" CACHE STRING "" FORCE)
endif()

FetchContent_MakeAvailable(freertos_kernel)

target_compile_definitions(freertos_config INTERFACE ${definitions})
target_compile_options(freertos_config INTERFACE ${options})


# Select the heap port.  values between 1-4 will pick a heap.
set(FREERTOS_HEAP "4" CACHE STRING "" FORCE)

# Select the native compile PORT
set(FREERTOS_PORT "TEMPLATE" CACHE STRING "" FORCE)

# Adding the FreeRTOS-Kernel subdirectory
#add_subdirectory(${FREERTOS_KERNEL_PATH} FreeRTOS-Kernel)

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


########################################################################################################################
############################################FAT#######################################################################

FetchContent_Declare( freertos_plus_fat
        GIT_REPOSITORY https://github.com/FreeRTOS/Lab-Project-FreeRTOS-FAT.git
        GIT_TAG        main #Note: Best practice to use specific git-hash or tagged version
        GIT_SUBMODULES "" # Don't grab any submodules since not latest
)

# ...

set( FREERTOS_PLUS_FAT_DEV_SUPPORT OFF CACHE BOOL "" FORCE)
# Select the native compile PORT
set( FREERTOS_PLUS_FAT_PORT "POSIX" CACHE STRING "" FORCE)
# Select the cross-compile PORT
if (CMAKE_CROSSCOMPILING)
    # Eg. Zynq 2019_3 version of port
    set(FREERTOS_PLUS_FAT_PORT "STM32F4xx" CACHE STRING "" FORCE)
endif()

FetchContent_MakeAvailable(freertos_plus_fat)

########################################################################################################################


file(GLOB_RECURSE SOURCES "Core/*.*" "Drivers/CMSIS/*.*" "Drivers/STM32F4xx_HAL_Driver/*.*" )
set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/STM32F411RETX_FLASH.ld)

add_link_options(-Wl,-gc-sections,--print-memory-usage,-Map=${PROJECT_BINARY_DIR}/${PROJECT_NAME}.map)
add_link_options(-mcpu=cortex-m4 -mthumb -mthumb-interwork)
add_link_options(-T ${LINKER_SCRIPT})

include_directories(Core/Inc Drivers/STM32F4xx_HAL_Driver/Inc
        Drivers/STM32F4xx_HAL_Driver/Inc/Legacy
        Drivers/CMSIS/Device/ST/STM32F4xx/Include
        Drivers/CMSIS/Include
)

set(CMAKE_THREAD_PREFER_PTHREAD FALSE)
set(COMMON_FLAGS "-mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard")
set(CMAKE_C_FLAGS "${COMMON_FLAGS} -Wall -fdata-sections -ffunction-sections ${CMAKE_C_FLAGS}")
set(CMAKE_ASM_FLAGS "${COMMON_FLAGS} ${CMAKE_ASM_FLAGS}")


add_executable(${PROJECT_NAME}.elf ${SOURCES} ${LINKER_SCRIPT})
add_definitions(-DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE)
set(HEX_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.hex)
set(BIN_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.bin)

target_link_libraries(${PROJECT_NAME}.elf freertos_kernel freertos_config freertos_plus_fat)
