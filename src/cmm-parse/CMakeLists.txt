target_sources(cmm-parser PRIVATE "./main.cpp"
                                  "./cmd.cpp")

target_link_libraries(cmm-parser cmm)
