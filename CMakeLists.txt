cmake_minimum_required(VERSION 3.18.1)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(
    cmm++
    LANGUAGES CXX
    VERSION 0.0.0
)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory("./src")
add_subdirectory("./tests")
