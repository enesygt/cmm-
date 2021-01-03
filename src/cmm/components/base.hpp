#ifndef CMM_COMPONENTS_BASE_HPP
#define CMM_COMPONENTS_BASE_HPP

#include <string>

#include <cmm/components/types.hpp>

namespace cmm {

class base_component {
   public:
    virtual void parce_block(const std::string &source) = 0;
    [[nodiscard]] virtual std::string to_html() const = 0;
    [[nodiscard]] component_type      get_type();

   protected:
    void set_type(component_type c);

   private:
    component_type type = component_type::undefined;
};

} // namespace cmm

#endif
