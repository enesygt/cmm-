cmake_minimum_required(VERSION 3.0.0)
project(cmm++)

include_directories("src")

file(GLOB cmm_SRC "src/cmm/*.cpp")
add_library(cmm STATIC ${cmm_SRC})

file(GLOB tests_SRC "tests/*.cpp")
add_executable(run_tests ${tests_SRC})
target_link_libraries(run_tests cmm)

# https://stackoverflow.com/questions/2368811/how-to-set-warning-level-in-cmake
if (MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -pedantic)
endif()
