cmake_minimum_required(VERSION 3.10)

# Force MinGW Generator
set(CMAKE_GENERATOR "MinGW Makefiles" CACHE INTERNAL "" FORCE)

# Set compilers before project() command
set(CMAKE_C_COMPILER "C:/msys64/ucrt64/bin/gcc.exe")
set(CMAKE_CXX_COMPILER "C:/msys64/ucrt64/bin/g++.exe")

project(e-learning)

# Set C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add source files
set(SOURCES
    src/main.cpp
    src/LinkedList.cpp
    src/HashTable.cpp
    src/Materi.cpp
    src/Tugas.cpp
    src/Kehadiran.cpp
    src/Auth.cpp
    src/MataKuliah.cpp
    src/Validator.cpp
)

# Add header files directory
include_directories(include)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Copy data files to build directory
file(COPY ${CMAKE_SOURCE_DIR}/data DESTINATION ${CMAKE_BINARY_DIR})