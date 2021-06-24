#include <cmm/components/types.hpp>

using cmm::markdown_component_type;

const char *cmm::describe(markdown_component_type m) {
    switch (m) {
    case markdown_component_type::undefined:
        return "Undefined";
    case markdown_component_type::atx_headings:
        return "Atx Heading";
    case markdown_component_type::setext_heading:
        return "Setext Heading";
    case markdown_component_type::indented_code_block:
        return "Indented Code Block";
    case markdown_component_type::fenced_code_block:
        return "Fenced Code Block";
    case markdown_component_type::fenced_code_block_opening:
        return "Fenced Code Block Opening";
    case markdown_component_type::fenced_code_block_closing:
        return "Fenced Code Block Closing";
    case markdown_component_type::fenced_code_block_inner:
        return "Fenced Code Block Inner";
    case markdown_component_type::paragraph:
        return "Paragraph";
    case markdown_component_type::block_quote:
        return "Block Quote";
    case markdown_component_type::ordered_list:
        return "Ordered List";
    case markdown_component_type::unordered_list:
        return "Unordered List";
    case markdown_component_type::thematic_break:
        return "Thematic Break";
    default:
        return "Not a markdown_component_type";
    }
}
