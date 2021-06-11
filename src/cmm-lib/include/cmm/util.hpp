#ifndef CMM_UTIL_HPP
#define CMM_UTIL_HPP

#include <iostream>
#include <string>

namespace cmm {

/**
 * @return A string containing the full contents of the stream
 */
std::string full_stream_read(std::istream &in);

}

#endif
