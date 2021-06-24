#ifndef CMM_TEXT_BLOCK_HPP
#define CMM_TEXT_BLOCK_HPP

#include <cmm/components.hpp>

#include <string>
#include <vector>

namespace cmm {

/**
 * A series of lines that end in two '\n'.
 *
 * Basically a paragraph.
 *
 * ~~~
 * Lorem ipsum dolor sit amet consectetur adipisicing elit. |
 * Facere provident velit, quibusdam, aliquam earum         |
 * corporis totam mollitia fugiat in vitae, placeat         |<- This is block 1
 * quaerat! Consequuntur eveniet quos a aliquid perferendis |
 * illo!  Earum!                                            |
 *
 * Lorem ipsum dolor sit amet consectetur adipisicing elit. |
 * Facere provident velit, quibusdam, aliquam earum         |
 * corporis totam mollitia fugiat in vitae, placeat         |<- This is block 2
 * quaerat! Consequuntur eveniet quos a aliquid perferendis |
 * illo!  Earum!                                            |
 * ~~~
 */
using text_block = std::string;

/**
 * Separates the source in text blocks.
 *
 * **Note:** Every line in the resulting text blocks will end in a \n.
 *
 * @see cmm::text_block
 */
std::vector<text_block> separate_blocks(const std::string& source);

/**
 * Identify what type of markdown component is the text block.
 *
 * @see cmm::markdown_component_type
 */
cmm::markdown_component_type identify_block_type(const text_block& source);

} // namespace cmm

#endif
