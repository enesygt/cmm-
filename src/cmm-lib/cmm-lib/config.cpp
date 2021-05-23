#include <cmm/config.hpp>

namespace cmm::config {

namespace imp {

[[nodiscard]] bool config::debug() const noexcept {
    return m_debug;
}

config &config::debug(bool d) noexcept {
    m_debug = d;
    return *this;
}

} // namespace imp

imp::config conf; // NOLINT

} // namespace cmm::config
