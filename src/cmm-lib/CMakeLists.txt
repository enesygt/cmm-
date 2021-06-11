set(cmm_lib_sources ./cmm-lib/cmm.cpp 
    ./cmm-lib/util.cpp
    ./cmm-lib/components/base.cpp
    ./cmm-lib/config.cpp
    ./cmm-lib/logger.cpp
    ./cmm-lib/inlines.cpp
    ./cmm-lib/escape_chars.cpp)

target_sources(cmm PRIVATE ${cmm_lib_sources})

install(TARGETS cmm
    DESTINATION lib)

install(DIRECTORY "./include/cmm"
    DESTINATION include
    FILES_MATCHING PATTERN "*.hpp")
