#ifndef CMM_COMPONENTS_BASE_HPP
#define CMM_COMPONENTS_BASE_HPP

#include <string>

#include <cmm/components/types.hpp>

namespace cmm {

class markdown_component {
   public:
    virtual void parce_block(const std::string &source) = 0;
    [[nodiscard]] virtual std::string to_html() const = 0;
    [[nodiscard]] markdown_component_type      get_type();

   protected:
    void set_type(markdown_component_type c);

   private:
    markdown_component_type type = markdown_component_type::undefined;
};

} // namespace cmm

#endif
