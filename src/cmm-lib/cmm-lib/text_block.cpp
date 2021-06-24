#include <cmm/text_block.hpp>
#include <cmm/logger.hpp>

#include <sstream>
#include <string>
#include <cassert>

using cmm::text_block;
using cmm::line;
using cmm::markdown_component_type;
using cmm::block_iterator;

line::line(const text_block &o, size_t f, size_t l)
    : origin(o), first(f), last(l) {}

char line::operator[](size_t p) const noexcept {
    return origin[first + p];
}


[[nodiscard]] const text_block & cmm::line::origin_block() const noexcept {
    return origin;
}


block_iterator block_iterator::begin(const text_block &t) noexcept {}

block_iterator block_iterator::end(const text_block &t) noexcept {}

auto block_iterator::operator*() const noexcept -> reference {

}

block_iterator&        block_iterator::operator++() {

}

bool             block_iterator::operator==(const block_iterator &other) {

}

bool             block_iterator::operator!=(const block_iterator &other) {

}

block_iterator block_iterator::operator++(int) {

}

std::vector<text_block> cmm::separate_blocks(const std::string& source) {
    std::vector<text_block> result;
    std::stringstream src(source);
    std::stringstream buffer;

    text_block temp;

    while (src) {
        // Clean up any leading \n
        while (src && src.peek() == '\n') {
            src.get();
        }

        // Read until you find a line with only one \n
        while (std::getline(src, temp)) {

            // If got to a \n push the result and clean the buffer.
            if (temp.empty()) {
                result.push_back(buffer.str());
                buffer.str("");
                break;
            }

            buffer << temp << '\n';
        }
    }

    // If the document ends in a single \n or none, then the last block was not
    // saved
    temp = buffer.str();
    if (!temp.empty()) {
        result.push_back(std::move(temp));
    }

    return result;
}

/**
 * @return The amount of spaces that where found from 'from', counting 'from'
 */
static size_t count_indentation(const text_block& b, size_t from);

static bool is_atx_heading(const text_block& source) noexcept;
static bool is_setext_heading(const text_block& source);
static bool is_indented_code_block(const text_block& source);
static bool is_fenced_code_block(const text_block& source);
static bool is_fenced_code_block_opening(const text_block& source);
static bool is_fenced_code_block_closing(const text_block& source);
static bool is_block_quote(const text_block& source);
static bool is_ordered_list(const text_block& source);
static bool is_unordered_list(const text_block& source);
static bool is_thematic_break(const text_block& source);

markdown_component_type cmm::identify_block_type(const text_block &source) {
    if (is_atx_heading(source)) {
        return markdown_component_type::atx_headings;
    }
    
    // If we found nothig special, then it is a paragraph.
    return markdown_component_type::paragraph;
}

static size_t count_indentation(const text_block& b, size_t from) {

}

// Check that every line starts with a #
static bool is_atx_heading(const text_block& source) noexcept {

    // Every line in the text_block is guaranteed to end in a '\n'.
    //
    // @see cmm::separate_blocks
    const size_t last_newline = source.size() - 1;
    assert(source[last_newline] == '\n');

    size_t current = 0;
    size_t next_newline = source.find('\n');

    // Find any line that does not start with a '#'
    while (true) {
        if (source[current] != '#') {
            return false;
        }

        if (next_newline == last_newline) {
            break;
        }

        current = next_newline + 1;
        next_newline = source.find('\n', current);
    }

    return true;
}
