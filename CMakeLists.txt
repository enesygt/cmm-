cmake_minimum_required(VERSION 3.18.1)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(
    cmm++
    LANGUAGES CXX
    VERSION 0.0.0
    )

set(CMAKE_CXX_STANDARD 17)

LIST(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

include(CTest)
include(Catch)

option(CMM_DEBUG "Enable debug assertions" OFF)
option(CMM_UNIT_TEST "Enable unit testing" OFF)

if (NOT CMM_DEBUG)
    add_compile_definitions(NDEBUG)
endif()

if (CMM_UNIT_TEST)
    add_subdirectory("./tests/unit")
endif ()

add_subdirectory("./src")

# https://stackoverflow.com/questions/2368811/how-to-set-warning-level-in-cmake
if (MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -pedantic)
endif()
