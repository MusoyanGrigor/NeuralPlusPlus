cmake_minimum_required(VERSION 3.30)
project(NeuralPlusPlus)

# Use C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include headers
include_directories(include)

# Automatically find all .cpp and .hpp files
file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE HEADERS "${CMAKE_SOURCE_DIR}/include/*.hpp")

# Ensure at least one source file exists
if(NOT SOURCES)
    message(FATAL_ERROR "No .cpp files found in src/")
endif()

# Print for debugging
message(STATUS "Source files: ${SOURCES}")
message(STATUS "Header files: ${HEADERS}")

# Create executable
add_executable(NeuralPlusPlus ${SOURCES} ${HEADERS})