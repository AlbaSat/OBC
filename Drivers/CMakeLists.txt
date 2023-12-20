add_library(${PROJECT_NAME}_DRIVERS_INCLUDE INTERFACE)
add_library(${PROJECT_NAME}_DRIVERS STATIC)

add_subdirectory(CMSIS)
add_subdirectory(STM32F4xx_HAL_Driver)

target_link_libraries(${PROJECT_NAME}_DRIVERS
    PUBLIC
        ${PROJECT_NAME}_DRIVERS_INCLUDE
)

target_compile_definitions(${PROJECT_NAME}_DRIVERS
    PUBLIC
        STM32F411xE
)
