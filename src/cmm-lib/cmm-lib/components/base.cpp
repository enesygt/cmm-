#include <cmm/components/base.hpp>

namespace cmm {

[[nodiscard]] markdown_component_type markdown_component::get_type() {
    return this->type;
}

void markdown_component::set_type(markdown_component_type c) {
    this->type = c;
}

} // namespace cmm
