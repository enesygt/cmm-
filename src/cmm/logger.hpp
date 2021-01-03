#ifndef CMM_LOGGER_HPP
#define CMM_LOGGER_HPP

#include <cmm/config.hpp>

namespace cmm {

class Logger {
   public:
    template<typename T>
    Logger &operator<<(const T &t) {
        if constexpr (config::debug_enabled) {
            if (config::debug) {
                std::cerr << t;
            }
        }
        return *this;
    }
};

extern Logger log; // NOLINT

} // namespace cmm

#endif
