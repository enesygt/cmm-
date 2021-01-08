#include <cmm/cmm.hpp>

namespace cmm {

std::string parce(const std::string &source) {
    std::string copy = source;
    process_inlines(copy);
    return copy;
}

} // namespace cmm
