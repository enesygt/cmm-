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
 * **Note:** This ones are created from the source using cmm::separate_blocks,
 * every line of the text block is guaranteed to end in a '\n'.
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

class line {
   public:
    line(const text_block &o, size_t f, size_t l);

    char  operator[](size_t p) const noexcept;

    [[nodiscard]] const text_block & origin_block() const noexcept;

   private:
    const text_block &origin;
    size_t            first = 0;
    size_t            last = 0;
};

/**
 * A LegacyInputIterator used to go thoug every line of the text_block
 */
class block_iterator {
   public:
    using value_type = line;
    using reference = value_type &;
    using pointer = value_type *;
    using iterator_category = std::input_iterator_tag;

    // No way to specify a begin, end special to text_block, because it is just
    // a std::string, so we will use this
    static block_iterator begin(const text_block &t) noexcept;
    static block_iterator end(const text_block &t) noexcept;

    reference       operator*() const noexcept;
    block_iterator &operator++();
    bool            operator==(const block_iterator &other);
    bool            operator!=(const block_iterator &other);
    block_iterator  operator++(int);
};

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
