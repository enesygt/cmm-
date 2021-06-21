#ifndef CMM_COMPONENTS_TYPES_HPP
#define CMM_COMPONENTS_TYPES_HPP

namespace cmm {

/**
 * List of posible types that the markdownd components can be
 */
enum class markdown_component_type {
    undefined,
    atx_headings,
    setext_heading,
    indented_code_block,
    fenced_code_block,
    html_block,
    link_reference,
    paragraph,
    block_quote,
    list
};

} // namespace cmm

#endif
