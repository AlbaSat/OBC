# This makes available target:
# ${PROJECT_NAME}_CORE_INCLUDE

add_subdirectory(Inc)

target_link_libraries(${PROJECT_NAME}.elf
    PUBLIC
        ${PROJECT_NAME}_CORE_INCLUDE
)

add_subdirectory(Src)
add_subdirectory(Startup)
