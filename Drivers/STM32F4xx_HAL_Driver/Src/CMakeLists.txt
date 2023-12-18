set(DRIVER_SOURCES
    stm32f4xx_hal.c
    stm32f4xx_hal_cortex.c
    stm32f4xx_hal_dma.c
    stm32f4xx_hal_dma_ex.c
    stm32f4xx_hal_exti.c
    stm32f4xx_hal_flash.c
    stm32f4xx_hal_flash_ex.c
    stm32f4xx_hal_flash_ramfunc.c
    stm32f4xx_hal_gpio.c
    stm32f4xx_hal_pwr.c
    stm32f4xx_hal_pwr_ex.c
    stm32f4xx_hal_rcc.c
    stm32f4xx_hal_rcc_ex.c
    stm32f4xx_hal_uart.c
)

add_library(${PROJECT_NAME}_DRIVERS STATIC)

target_sources(${PROJECT_NAME}_DRIVERS
    PRIVATE
        ${DRIVER_SOURCES}
)

target_link_libraries(${PROJECT_NAME}_DRIVERS
    PUBLIC
        ${PROJECT_NAME}_DRIVERS_INCLUDE
)
