#ifndef CMM_TEXT_BLOCK_HPP
#define CMM_TEXT_BLOCK_HPP

#include <cmm/components.hpp>

#include <iterator>
#include <string>
#include <vector>

namespace cmm {

/**
 * A series of lines.
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
using text_block = std::vector<std::string>;


/**
 * Separates the source in text blocks.
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

/**
 * @return The amount of spaces found at the start of a line, or npos if all the
 * characters are spaces
 */
size_t count_indentation(const std::string& s);

/**
*  The indentation of the line must be checked regarding the above line. 
*/
bool check_indentation(const std::string &s
                       ,const size_t indentation
                       ,const size_t last_indentation);


} // namespace cmm

std::ostream& operator<<(std::ostream& o, const cmm::text_block& t);
std::string operator+(const std::string& rhs, const cmm::text_block& lhs);

#endif
