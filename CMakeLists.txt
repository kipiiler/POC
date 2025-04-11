cmake_minimum_required(VERSION 3.16)

project(POC VERSION 1.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Source files
set(SOURCES
    src/main.cpp
    src/Square.cpp
    src/Shader.cpp
    src/Texture.cpp
    src/TextureSquare.cpp
)

add_executable(POC ${SOURCES})

find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

target_link_libraries(POC PRIVATE
    glfw
    glad::glad
    glm::glm
)
