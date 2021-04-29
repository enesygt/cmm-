#ifndef CMM_CONFIG_HPP
#define CMM_CONFIG_HPP

#include <iostream>
#include <ostream>

namespace cmm::config {

constexpr bool debug_enabled = true;

namespace imp {

class config {
   public:
    [[nodiscard]] bool debug() const;
    config &           debug(bool d);

   private:
    bool m_debug = false;
};

} // namespace imp

extern imp::config conf; //NOLINT

} // namespace cmm::config

#endif
