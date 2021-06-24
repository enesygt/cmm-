#ifndef CMM_COMPONENTS_TYPES_HPP
#define CMM_COMPONENTS_TYPES_HPP

namespace cmm {

/**
 * List of posible types that the markdownd components can be
 *
 * See tests/unit/block_examples.hpp for full examples
 */
enum class markdown_component_type {
    undefined,

    // # Like this
    atx_headings,

    // Like this
    // =========
    setext_heading,

    //
    //     Like this
    //
    indented_code_block,


    // ```
    // Like this
    // ```
    fenced_code_block,

    // And this ones are here because fenced code blocks can expand over
    // multiple text blocks
    fenced_code_block_opening,
    fenced_code_block_closing,
    fenced_code_block_inner,

    // Just normal text
    paragraph,

    // > Like this
    block_quote,

    // 1. Like
    // 2. This
    ordered_list,

    // * Like
    // * this
    unordered_list,

    // ---
    thematic_break
};

} // namespace cmm

#endif
