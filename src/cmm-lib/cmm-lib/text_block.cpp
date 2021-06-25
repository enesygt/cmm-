#include <cmm/text_block.hpp>
#include <cmm/logger.hpp>

#include <sstream>
#include <string>
#include <cassert>

using cmm::text_block;
using cmm::markdown_component_type;

std::ostream& operator<<(std::ostream& o, const cmm::text_block& t) {
    for (const auto & b : t) {
        o << b << '\n';
    }
    return o;
}



std::vector<text_block> cmm::separate_blocks(const std::string& source) {
    std::vector<text_block> result;
    std::stringstream src(source);
    std::string temp;
    text_block buffer;



    while (src) {
        // Clean up any leading \n
        while (src && src.peek() == '\n') {
            src.get();
        }

        // Read until you find a line with only one \n
        while (std::getline(src, temp)) {

            // If got to a \n push the result and clean the buffer.
            if (temp.empty()) {
                result.push_back(buffer);
                buffer.clear();
                break;
            }

            buffer.push_back(temp);
        }
    }

    // If the document ends in a single \n or none, then the last block was not
    // saved
    // temp = buffer.str();
    // if (!temp.empty()) {
    //     result.push_back(std::move(temp));
    // }
    if (!buffer.empty()) {
        result.push_back(buffer);
    }

    return result;
}

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
    // if (is_atx_heading(source)) {
    //     return markdown_component_type::atx_headings;
    // }
    
    // If we found nothig special, then it is a paragraph.
    return markdown_component_type::paragraph;
}

// Check that every line starts with a #
// static bool is_atx_heading(const text_block& source) noexcept {
// 
//     // Every line in the text_block is guaranteed to end in a '\n'.
//     //
//     // @see cmm::separate_blocks
//     const size_t last_newline = source.size() - 1;
//     assert(source[last_newline] == '\n');
// 
//     size_t current = 0;
//     size_t next_newline = source.find('\n');
// 
//     // Find any line that does not start with a '#'
//     while (true) {
//         if (source[current] != '#') {
//             return false;
//         }
// 
//         if (next_newline == last_newline) {
//             break;
//         }
// 
//         current = next_newline + 1;
//         next_newline = source.find('\n', current);
//     }
// 
//     return true;
// }
