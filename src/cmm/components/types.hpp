#ifndef CMM_COMPONENTS_TYPES_HPP
#define CMM_COMPONENTS_TYPES_HPP

namespace cmm {

enum class component_type {
    undefined,
    atx_headings,
    setext_heading,
    indented_code_block,
    fenced_code_block,
    html_block
};

} // namespace cmm

#endif
