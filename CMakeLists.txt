# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.15)

# Set the target system for cross compilation
set(CMAKE_SYSTEM_NAME Generic)

# Set compilers
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)
set(CMAKE_AR arm-none-eabi-ar)
set(CMAKE_OBJCOPY arm-none-eabi-objcopy)
set(CMAKE_OBJDUMP arm-none-eabi-objdump)
set(SIZE arm-none-eabi-size)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# Declare the project
project(OBC C CXX ASM)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 17)

# Include FetchContent
include(FetchContent)

# Define sources and linker script
#file(GLOB_RECURSE SOURCES "Core/*.*" "Drivers/*.*")
set(SOURCES
        # Core/Src/
        Core/Src/freertos.c
        Core/Src/main.c
        Core/Src/stm32f4xx_hal_msp.c
        Core/Src/stm32f4xx_it.c
        Core/Src/syscalls.c
        Core/Src/sysmem.c
        Core/Src/system_stm32f4xx.c
        Core/Src/vTask1.c

        # Drivers/STM32F4xx_HAL_Driver/Src/
        Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.c
        Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma.c
        Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_exti.c
        Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ex.c
        Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.c
        Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr_ex.c
        Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc_ex.c
        Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.c
        Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma_ex.c
        Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash.c
        Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ramfunc.c
        Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr.c
        Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc.c
        Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_uart.c

)

set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/STM32F411RETX_FLASH.ld)

# Add link options
add_link_options(-Wl,-gc-sections,--print-memory-usage,-Map=${PROJECT_BINARY_DIR}/${PROJECT_NAME}.map)
add_link_options(-T ${LINKER_SCRIPT})

# Include directories
include_directories(Core/Inc Drivers/STM32F4xx_HAL_Driver/Inc
        Drivers/STM32F4xx_HAL_Driver/Inc/Legacy
        Drivers/CMSIS/Device/ST/STM32F4xx/Include
        Drivers/CMSIS/Include
)

# Set common flags
set(COMMON_FLAGS "-mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard -specs=nano.specs -specs=nosys.specs")
set(CMAKE_C_FLAGS "${COMMON_FLAGS} -Wall -fdata-sections -ffunction-sections ${CMAKE_C_FLAGS}")
set(CMAKE_CXX_FLAGS "${COMMON_FLAGS} -Wall -fdata-sections -ffunction-sections ${CMAKE_CXX_FLAGS}")
set(CMAKE_ASM_FLAGS "${COMMON_FLAGS} ${CMAKE_ASM_FLAGS}")
add_compile_options(-g -ggdb)

# Fetch FreeRTOS
FetchContent_Declare(freertos_kernel
        GIT_REPOSITORY https://github.com/FreeRTOS/FreeRTOS-Kernel.git
        GIT_TAG V10.6.2 #Note: Best practice to use specific git-hash or tagged version
)

## FreeRTOS config
add_library(freertos_config INTERFACE)

target_include_directories(freertos_config SYSTEM
        INTERFACE
        Core/Inc
)

target_compile_definitions(freertos_config
        INTERFACE
        projCOVERAGE_TEST=0
)

set(FREERTOS_HEAP "3" CACHE STRING "" FORCE)
set(FREERTOS_PORT "GCC_ARM_CM4F" CACHE STRING "" FORCE)

target_compile_definitions(freertos_config INTERFACE ${definitions})
target_compile_options(freertos_config INTERFACE ${options})
FetchContent_MakeAvailable(freertos_kernel)

# Fetch FreeRTOS+FAT
FetchContent_Declare(freertos_plus_fat
        GIT_REPOSITORY https://github.com/FreeRTOS/Lab-Project-FreeRTOS-FAT.git
        GIT_TAG 25129e5221ae6ebf9d88e11f78d33c68edb254fb #Note: Best practice to use specific git-hash or tagged version
        GIT_SUBMODULES "" # Don't grab any submodules since not latest
)

set(FREERTOS_PLUS_FAT_DEV_SUPPORT OFF CACHE BOOL "" FORCE)
# Select the native compile PORT
set(FREERTOS_PLUS_FAT_PORT POSIX CACHE STRING "")
# Select the cross-compile PORT
if (CMAKE_CROSSCOMPILING)
    # Eg. Zynq 2019_3 version of port
    set(FREERTOS_PLUS_FAT_PORT STM32F4xx CACHE STRING "")
endif ()

FetchContent_MakeAvailable(freertos_plus_fat)

# Define target
add_executable(${PROJECT_NAME}.elf ${SOURCES} ${LINKER_SCRIPT})
add_definitions(-DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE)

# Link libraries
target_link_libraries(${PROJECT_NAME}.elf freertos_kernel freertos_config freertos_plus_fat)