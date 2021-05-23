#ifndef CMM_LOGGER_HPP
#define CMM_LOGGER_HPP

#include <type_traits>
#include <cmm/config.hpp>

namespace cmm {

class Logger final {
   public:
    template<typename T>
    Logger &operator<<(const T &t) {
        if constexpr (config::debug_enabled) {
            if (config::conf.debug()) {
                std::clog << t;
            }
        }
        return *this;
    }
};

/// The logger used for debbugin
extern Logger log; // NOLINT

} // namespace cmm

#endif
