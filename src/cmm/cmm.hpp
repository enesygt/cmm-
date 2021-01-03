#ifndef CMM_MAIN_INCLUDE_FILE_HPP
#define CMM_MAIN_INCLUDE_FILE_HPP

#include <cmm/config.hpp>
#include <cmm/logger.hpp>
#include <cmm/util.hpp>

namespace cmm {

/// Parces the markdown source returning the html version
std::string parce(const std::string &source);

}

#endif
