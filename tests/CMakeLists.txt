add_executable(run_tests)
target_sources(run_tests PRIVATE "./main.cpp"
                                 "./inlines.cpp")
target_include_directories(run_tests PRIVATE "../src/cmm-lib/include")
target_link_libraries(run_tests cmm)

catch_discover_tests(run_tests)
