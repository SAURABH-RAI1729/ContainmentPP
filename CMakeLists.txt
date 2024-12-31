cmake_minimum_required(VERSION 3.22)

# Project name and version
project(ContainmentPP VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Define project directories
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(MODEL_DIR ${CMAKE_SOURCE_DIR}/models)
set(EXAMPLES_DIR ${CMAKE_SOURCE_DIR}/examples)

# Include directories for all targets
include_directories(${INCLUDE_DIR} ${MODEL_DIR})

# Define source files for the library
set(SOURCES
    ${SRC_DIR}/Solver.cpp
    ${SRC_DIR}/SimulationEngine.cpp
    ${MODEL_DIR}/SIRModel.cpp
    ${MODEL_DIR}/SEIRModel.cpp
)

# Add library target
add_library(ContainmentPP STATIC ${SOURCES})

# Specify include directories for the library
target_include_directories(ContainmentPP PUBLIC ${INCLUDE_DIR} ${MODEL_DIR})

# Add the example executable target
add_executable(example ${EXAMPLES_DIR}/Main.cpp)

# Link the library with the example executable
target_link_libraries(example PRIVATE ContainmentPP)

# Set output directories for build artifacts
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
