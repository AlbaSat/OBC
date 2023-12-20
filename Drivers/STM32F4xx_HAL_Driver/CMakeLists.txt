target_include_directories(${PROJECT_NAME}_DRIVERS_INCLUDE
    INTERFACE
        Inc
        Inc/Legacy
)

# ${PROJECT_NAME}_DRIVERS
add_subdirectory(Src)
