cmake_minimum_required(VERSION 3.18.1)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


project(
    cmm++
    LANGUAGES CXX
    VERSION 0.0.0
)

LIST(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

include(CTest)
include(Catch)

set(CMAKE_CXX_STANDARD 17)

if (NOT CMM_DEBUG)
    add_compile_definitions(NDEBUG)
endif()

if (CMM_TEST)
    add_subdirectory("./tests")
endif ()

add_subdirectory("./src")
