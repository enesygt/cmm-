#ifndef CMM_CONFIG_HPP
#define CMM_CONFIG_HPP

#include <iostream>

namespace cmm::config {

constexpr bool debug_enabled = true;

namespace imp {

/**
 * Class that holds the configuration, for now it only works for debug purposes.
 * I might delete it latter.
 */
class config {
   public:
    [[nodiscard]] bool debug() const noexcept;
    config &           debug(bool d) noexcept;

   private:
    bool m_debug = false;
};

} // namespace imp

extern imp::config conf; //NOLINT

} // namespace cmm::config

#endif
