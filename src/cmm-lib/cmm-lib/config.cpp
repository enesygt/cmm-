#include <cmm/config.hpp>

using cmm::config::imp::config;


[[nodiscard]] bool config::debug() const noexcept {
    return m_debug;
}

config &config::debug(bool d) noexcept {
    m_debug = d;
    return *this;
}


config cmm::config::conf; // NOLINT

