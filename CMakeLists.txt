# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.18)

# Declare the project
project(OBC
    VERSION 0.1
    DESCRIPTION "On board software for Albasat OBC"
    LANGUAGES C CXX ASM)

# Do not allow in-source build
if( ${PROJECT_SOURCE_DIR} STREQUAL ${PROJECT_BINARY_DIR} )
    message( FATAL_ERROR "In-source build is not allowed. Please build in a separate directory, such as ${PROJECT_SOURCE_DIR}/build." )
endif()

# Find git - this makes available GIT_FOUND and GIT_EXECUTABLE
find_package(Git)

# Do not allow build without submodules
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
    execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                    RESULT_VARIABLE GIT_SUBMOD_RESULT)
    if(NOT GIT_SUBMOD_RESULT EQUAL "0")
        message(FATAL_ERROR "git submodule update --init --recursive failed with ${GIT_SUBMOD_RESULT}, please checkout submodules.")
    endif()
else()
    message(WARNING "Either git not found or this is not a git repository. Cannot check for submodules.")
endif()

# Set the standard
set(CMAKE_CXX_STANDARD 17 CACHE STRING "The C++ standard to use")
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_C_STANDARD 17 CACHE STRING "The C standard to use")
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Set common flags
set(COMMON_FLAGS "-mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard -specs=nano.specs -specs=nosys.specs")
set(CMAKE_C_FLAGS "${COMMON_FLAGS} -Wall -fdata-sections -ffunction-sections ${CMAKE_C_FLAGS}")
set(CMAKE_CXX_FLAGS "${COMMON_FLAGS} -Wall -fdata-sections -ffunction-sections ${CMAKE_CXX_FLAGS}")
set(CMAKE_ASM_FLAGS "${COMMON_FLAGS} ${CMAKE_ASM_FLAGS}")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_compile_options(-g -ggdb)

# Set linker
set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/STM32F411RETX_FLASH.ld)

# Add link options
add_link_options(-Wl,-gc-sections,--print-memory-usage,-Map=${PROJECT_BINARY_DIR}/${PROJECT_NAME}.map)
add_link_options(-T ${LINKER_SCRIPT})

# Create executable and add link script to sources
add_executable(${PROJECT_NAME}.elf)
#target_sources(${PROJECT_NAME}.elf ${LINKER_SCRIPT})
set_target_properties(${PROJECT_NAME}.elf PROPERTIES LINK_DEPENDS ${LINKER_SCRIPT})


add_subdirectory(Drivers)
add_subdirectory(Core)

target_link_libraries(${PROJECT_NAME}.elf
    PRIVATE
        ${PROJECT_NAME}_DRIVERS
) 
target_link_libraries(${PROJECT_NAME}_DRIVERS
    PRIVATE
        ${PROJECT_NAME}_CORE_INCLUDE
)

# FreeRTOS config
add_library(freertos_config INTERFACE)

#target_include_directories(freertos_config SYSTEM
#    INTERFACE
#        Core/Inc
#        Drivers/STM32F4xx_HAL_Driver/Inc
#        Drivers/STM32F4xx_HAL_Driver/Inc/Legacy
#        Drivers/CMSIS/Device/ST/STM32F4xx/Include
#        Drivers/CMSIS/Device/Include
#        Drivers/CMSIS/Include
#)

target_link_libraries(freertos_config
    INTERFACE
        ${PROJECT_NAME}_DRIVERS_INCLUDE
        ${PROJECT_NAME}_CORE_INCLUDE
) 

target_compile_definitions(freertos_config
    INTERFACE
        projCOVERAGE_TEST=0
)

set(FREERTOS_HEAP "3" CACHE STRING "" FORCE)
set(FREERTOS_PORT "GCC_POSIX" CACHE STRING "")
if (CMAKE_CROSSCOMPILING)
    set(FREERTOS_PORT "GCC_ARM_CM4F" CACHE STRING "" FORCE)
endif()

target_compile_definitions(freertos_config INTERFACE ${definitions})
target_compile_options(freertos_config INTERFACE ${options})

set(FREERTOS_PATH "${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/FreeRTOS-Kernel" CACHE STRING "" FORCE)
add_subdirectory(${FREERTOS_PATH})

# Select the native compile PORT
set(FREERTOS_PLUS_FAT_PORT POSIX CACHE STRING "")
# Select the cross-compile PORT
if (CMAKE_CROSSCOMPILING)
    # Eg. Zynq 2019_3 version of port
    set(FREERTOS_PLUS_FAT_PORT STM32F4XX CACHE STRING "" FORCE)
endif ()
set(FREERTOS_PLUS_FAT_FETCH_FREERTOS OFF)

set(FAT_FREERTOS_PATH "${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Lab-Project-FreeRTOS-FAT" CACHE STRING "" FORCE)
add_subdirectory(${FAT_FREERTOS_PATH})

# We don't use SD card
set_source_files_properties(${FAT_FREERTOS_PATH}/portable/STM32F4xx/ff_sddisk.c
    TARGET_DIRECTORY freertos_plus_fat_port
    PROPERTIES HEADER_FILE_ONLY ON
)


add_definitions(-DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE)

# Link libraries
target_link_libraries(${PROJECT_NAME}.elf PUBLIC freertos_kernel freertos_config freertos_plus_fat freertos_plus_fat_port)

