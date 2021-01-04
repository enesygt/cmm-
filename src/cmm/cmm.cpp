#include <cmm/cmm.hpp>

namespace cmm {

std::string parce(const std::string &source) {
    std::string copy = source;
    process_strong_emphasis(copy);
    process_emphasis(copy);
    return copy;
}

} // namespace cmm
