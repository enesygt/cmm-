#include <cmm/components/base.hpp>

namespace cmm {

[[nodiscard]] component_type base_component::get_type() {
    return this->type;
}

void base_component::set_type(component_type c) {
    this->type = c;
}

} // namespace cmm
