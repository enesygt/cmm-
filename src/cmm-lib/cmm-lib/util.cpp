#include <sstream>
#include <cmm/util.hpp>

namespace cmm {

std::string full_stream_read(std::istream &in) {
    std::stringstream ss{};

    std::string read_data;
    while (std::getline(in, read_data)) {
        ss << read_data << '\n';
    }

    return ss.str();
}

} // namespace cmm
