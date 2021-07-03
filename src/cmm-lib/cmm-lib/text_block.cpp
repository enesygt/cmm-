#include <cmm/text_block.hpp>
#include <cmm/logger.hpp>
#include <cmm/syntax_error.hpp>

#include <sstream>
#include <string>
#include <algorithm>
#include <cassert>

using cmm::text_block;
using cmm::markdown_component_type;

std::ostream& operator<<(std::ostream& o, const cmm::text_block& t) {
    for (const auto & b : t) {
        o << b << '\n';
    }
    return o;
}


std::string operator+(const std::string& rhs, const text_block& lhs) {
    std::string result(rhs);
    for (const auto& b : lhs) {
        result += b;
        result += '\n';
    }
    return result;
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

    if (!buffer.empty()) {
        result.push_back(buffer);
    }

    return result;
}

size_t cmm::count_indentation(const std::string& s) {
    for (size_t i = 0; i < s.size(); i++) {
        if (s[i] != ' ') {
            return i;
        }
    }
    return std::string::npos;
}

bool cmm::check_indentation(const std::string &line,
                            const size_t indentation,
                            const size_t last_indentation) {

 
    bool indentation_status = true;

    if (indentation == std::string::npos) {
        std::string error_message = std::string("At block:\n") + line;
        error_message += "\nThere is la line only formed by white spaces, "
                         "remove it to create 2 separate blocks";
        throw cmm::syntax_error(error_message);
    }

    if ((indentation > size_t{3})
        && (indentation != last_indentation + size_t{2})
        && (indentation != last_indentation)) {
        indentation_status =  false;
    }

    return indentation_status;
}


static bool is_atx_heading(const text_block& source);
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
	if (is_unordered_list(source)) {
        return markdown_component_type::unordered_list;
    }
    if (is_ordered_list(source)) {
        return markdown_component_type::ordered_list;
    }
    
    // If we found nothig special, then it is a paragraph.
    return markdown_component_type::paragraph;
}

static bool is_atx_heading(const text_block& source) {
    auto starts_with_hash = [&](const std::string& line) -> bool {
        auto indentation = cmm::count_indentation(line);

        if (indentation == std::string::npos) {
            std::string error_message = std::string("At block:\n") + source;
            error_message += "\nThere is la line only formed by white spaces, "
                             "remove it to create 2 separate blocks";
            throw cmm::syntax_error(error_message);
        }

        if (indentation > 3) {
            return false;
        }

        return line[indentation] == '#';
    };
    return std::all_of(source.begin(), source.end(), starts_with_hash);
}

static bool is_unordered_list(const text_block &source) {

    bool unordered_list_flag = false;

    size_t last_indentation = 0;

    for (const auto &line : source) {

        auto indentation = cmm::count_indentation(line);

        if (false== cmm::check_indentation(line, indentation, last_indentation)) {
            unordered_list_flag = false;
            break;
        }

         if (line[indentation] == '*' || line[indentation] == '-'
            || line[indentation] == '+') {
            unordered_list_flag = true;
            last_indentation = indentation;
        }
    }

    return unordered_list_flag;
}

static bool is_ordered_list(const text_block &source) {

    size_t last_indentation = 0;
    static bool ordered_list_flag = false;

    for (const auto &line : source) {

        auto indentation = cmm::count_indentation(line);

        if (false == cmm::check_indentation(line, indentation, last_indentation))
        {
            ordered_list_flag = false;
            break;
        }

         last_indentation = indentation;
 
         if ('1' == line[indentation] && 
            '.' == line[indentation + size_t{1}]) {
           ordered_list_flag = true;
         }
       

    }

    return ordered_list_flag;
}

