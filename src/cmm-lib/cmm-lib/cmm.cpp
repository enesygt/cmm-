#include <cmm/cmm.hpp>

namespace cmm {

std::string parce(const std::string &source) {
    std::string result = process_inlines(source);
    return result;
}

} // namespace cmm
