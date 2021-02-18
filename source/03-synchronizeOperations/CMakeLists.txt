# Define source files
file(GLOB SOURCES
    "${CMAKE_CURRENT_LIST_DIR}/private/03-synchronizeOperations/*.cpp")

# Define header files
file(GLOB HEADERS
    "${CMAKE_CURRENT_LIST_DIR}/public/03_synchronizeOperations/*.h")

# Create 01_threadManagement executable
add_executable(03_synchronizeOperations
    ${SOURCES}
    ${HEADERS})

# Add private and public include directories
target_include_directories(03_synchronizeOperations
    PUBLIC public
    PRIVATE private)

# Define the output directory
if(DEFINED MULTITHREADING_OUTPUT_DIR)
        set_target_properties(03_synchronizeOperations
            PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY "${MULTITHREADING_OUTPUT_DIR}/03_synchronizeOperations")
endif()


