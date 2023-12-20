set(SOURCES
    freertos.c
    main.c
    stm32f4xx_hal_msp.c
    stm32f4xx_it.c
    syscalls.c
    sysmem.c
    system_stm32f4xx.c
    vTask1.c
)

target_sources(${PROJECT_NAME}.elf
    PRIVATE
        ${SOURCES}
)

