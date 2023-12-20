set(SOURCES
    freertos.c
    main.c
    stm32f4xx_hal_msp.c
    stm32f4xx_it.c
    syscalls.c
    sysmem.c
    system_stm32f4xx.c
    task_fat_init.c
)

target_sources(${PROJECT_NAME}.elf
    PRIVATE
        ${SOURCES}
)

target_link_libraries(${PROJECT_NAME}.elf
    PUBLIC
        ${PROJECT_NAME}_CORE_INCLUDE
)
