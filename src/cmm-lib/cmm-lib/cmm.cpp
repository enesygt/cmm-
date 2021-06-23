#include <cmm/cmm.hpp>

using cmm::process_inlines;

std::string cmm::parce(const std::string &source) {
    std::string result = process_inlines(source);
    return result;
}
