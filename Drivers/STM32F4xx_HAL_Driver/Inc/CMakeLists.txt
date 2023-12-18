add_library(${PROJECT_NAME}_DRIVERS_INCLUDE INTERFACE)

target_include_directories(${PROJECT_NAME}_DRIVERS_INCLUDE
    INTERFACE
        .
        ./Legacy
)
