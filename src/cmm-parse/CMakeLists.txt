target_sources(cmm-parse PRIVATE "./main.cpp"
                         "./cmd.cpp")

target_link_libraries(cmm-parse cmm)
