# Define source files
file(GLOB SOURCES
    "${CMAKE_CURRENT_LIST_DIR}/private/01_threadManagement/*.cpp")

# Define header files
file(GLOB HEADERS
    "${CMAKE_CURRENT_LIST_DIR}/public/01_threadManagement/*.h")

# Create 01_threadManagement executable
add_executable(01_threadManagement
    ${SOURCES}
    ${HEADERS})

# Add private and public include directories
target_include_directories(01_threadManagement
    PUBLIC public
    PRIVATE private)

# Define the output directory
if(DEFINED MULTITHREADING_OUTPUT_DIR)
        set_target_properties(01_threadManagement
            PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY "${MULTITHREADING_OUTPUT_DIR}/01_threadManagement")
endif()
