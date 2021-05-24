add_library(cmm)
add_executable(cmm-parser)

target_include_directories(cmm PRIVATE "./cmm-lib/include")
target_include_directories(cmm-parser PRIVATE "./cmm-lib/include")

add_subdirectory("./cmm-lib")
add_subdirectory("./cmm-parse")
