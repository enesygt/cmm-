#include <cmm/config.hpp>

namespace cmm::config {

namespace imp {

[[nodiscard]] bool config::debug() const {
    return m_debug;
}

config &config::debug(bool d) {
    m_debug = d;
    return *this;
}

} // namespace imp

imp::config conf; // NOLINT

} // namespace cmm::config
