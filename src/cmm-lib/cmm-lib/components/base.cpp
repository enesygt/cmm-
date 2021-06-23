#include <cmm/components/base.hpp>

using cmm::markdown_component;
using cmm::markdown_component_type;

[[nodiscard]] markdown_component_type markdown_component::get_type() {
    return this->type;
}

void markdown_component::set_type(markdown_component_type c) {
    this->type = c;
}
