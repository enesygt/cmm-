#include <cmm/inlines.hpp>
#include <cmm/logger.hpp>

#include <sstream>

namespace cmm {

constexpr char escape_char = '\\';

static bool is_escapable_character(char c);

void process_inlines(std::string &source) {
    using sz_t = std::string::size_type;

    std::stringstream result;
    sz_t index = 0;

    auto write_n = [&](sz_t n) -> void {
        for (sz_t i = 0; i < n; i++) {
            result << source[index++];
        }
    };
    auto ignore_n = [&](sz_t n) -> void {
        index += n;
    };
    auto next_is_in_range = [&](void) -> bool {
        return (index + 1) < source.size();
    };

    for (; index < source.size(); index++) {
        switch (source[index]) {

        // Backslash escapes
        case escape_char: {
            //if (!next_is_in_range()) {
            //    result << source[index];
            //    break;
            //}

            //if (is_escapable_character(source[index + 1])) {

            //}
            //break;
        }

        // Code spans
        case '`': {

            break;
        }

            // Emphasis and strong emphasis
        case '*':
        case '_': {

            break;
        }

            // Links
        case '[': {

            break;
        }

            // Images
        case '!': {

            break;
        }

        default: {

            break;
        }
        }
    }
}

static bool is_escapable_character(char c) {
    switch (c) {
    case '\\':
    case '\'':
    case '!':
    case '"':
    case '#':
    case '$':
    case '%':
    case '&':
    case '(':
    case ')':
    case '*':
    case '+':
    case ',':
    case '-':
    case '.':
    case '/':
    case ':':
    case ';':
    case '<':
    case '=':
    case '>':
    case '?':
    case '@':
    case '[':
    case ']':
    case '^':
    case '_':
    case '`':
    case '{':
    case '|':
    case '}':
    case '~':
        return true;
    default:
        return false;
    }
}

} // namespace cmm
