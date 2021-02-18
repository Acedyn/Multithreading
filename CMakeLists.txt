# Cmake version 3.0 or newer required
cmake_minimum_required(VERSION 3.0)

# Create compile command json file for clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(MultiThreadingExercices
    VERSION 1.0
    LANGUAGES CXX
    DESCRIPTION "Exercices from ARTFX's workshop on multithreading")

########################################
## Components
########################################

# Include source/01_threadManagement
add_subdirectory(source/01_threadManagement)

# Include source/02_shareData
add_subdirectory(source/02_shareData)

# Include source/03-synchronizeOperationso
add_subdirectory(source/03-synchronizeOperations)

# Include source/04_memoryAndAtomicTypes
# add_subdirectory(source/04_memoryAndAtomicTypes)
