add_library(cmm)
add_executable(cmm-parse)

target_include_directories(cmm PRIVATE "./cmm-lib/include")
target_include_directories(cmm-parse PRIVATE "./cmm-lib/include")

add_subdirectory("./cmm-lib")
add_subdirectory("./cmm-parse")
