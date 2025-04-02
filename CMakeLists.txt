# Minimum CMake version required
cmake_minimum_required(VERSION 3.16)

# Project name and version
project(POC VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add an executable target
add_executable(POC src/main.cpp)