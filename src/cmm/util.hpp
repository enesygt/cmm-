#ifndef CMM_UTIL_HPP
#define CMM_UTIL_HPP

#include <iostream>
#include <string>

#include <cmm/logger.hpp>

namespace cmm {

/// Reads the stream until if finds the EOF character
std::string full_stream_read(std::istream &in);

}

#endif
