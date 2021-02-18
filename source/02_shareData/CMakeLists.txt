# Define source files
file(GLOB SOURCES
    "${CMAKE_CURRENT_LIST_DIR}/private/02_shareData/*.cpp")

# Define header files
file(GLOB HEADERS
    "${CMAKE_CURRENT_LIST_DIR}/public/02_shareData/*.h")

# Create 01_threadManagement executable
add_executable(02_shareData
    ${SOURCES}
    ${HEADERS})

# Add private and public include directories
target_include_directories(02_shareData
    PUBLIC public
    PRIVATE private)

# Define the output directory
if(DEFINED MULTITHREADING_OUTPUT_DIR)
        set_target_properties(02_shareData
            PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY "${MULTITHREADING_OUTPUT_DIR}/02_shareData")
endif()

