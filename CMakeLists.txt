cmake_minimum_required(VERSION 3.16)

project(POC VERSION 1.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(POC src/main.cpp)

find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)

target_link_libraries(POC PRIVATE
    glfw
    glad::glad
)