#include <cmm/inlines.hpp>
#include <cmm/logger.hpp>

#include <sstream>

namespace cmm {

using sz_t = std::string::size_type;

struct InlineState final {
    const std::string &source; // NOLINT
    std::stringstream &result; // NOLINT
    sz_t &             index;  // NOLINT

    // Code spans
    bool in_code_span = false;     // NOLINT
    sz_t number_of_backsticks = 0; // NOLINT

    // Emphasis
    bool in_emphasis = false; // NOLINT

    // Strong emphasis
    bool in_strong_emphasis = false; // NOLINT

    [[nodiscard]] bool is_valid(void) const {
        return index < source.size();
    }

    // Returns the current character
    [[nodiscard]] char current(void) const noexcept {
        return source[index];
    }

    // Returns the next character
    [[nodiscard]] char next(void) const noexcept {
        return source[index + 1];
    }

    [[nodiscard]] bool next_is_in_range(void) const noexcept {
        return (index + 1) < source.size();
    };

    // Writes n characters to the resutl
    void write_n(sz_t n) {
        for (sz_t i = 0; i < n; i++) {
            result << source[index++];
        }
    };

    // Writes str to the result
    void write(const char * const str) {
        result << str;
    }

    void ignore_n(sz_t n) {
        index += n;
    };

    // Counts the times a character is found, from the current position in the
    // source
    [[nodiscard]] sz_t count_ocurrences(char c) const noexcept{
        sz_t count = 0;
        while (source[index + count] == c) {
            ++count;
        }
        return count;
    }
};

constexpr char escape_char = '\\';
constexpr char backstick = '`';

static bool is_escapable_character(char c) noexcept;
static const char* escape_character(char c) noexcept;

std::string process_inlines(const std::string &source) {
    std::stringstream result;
    sz_t              index = 0;

    InlineState state = {source, result, index};

    /*
     * We will go character by character, acting acording to the state for the
     * code spans, emphasis, and strong emphasis.
     *
     * The links and images will be treated inline
     */
    while (state.is_valid()) {
        switch (state.current()) {

        // Backslash escapes
        case escape_char: {
            if (!state.next_is_in_range()) {
                state.write_n(1);
                break;
            }

            char next = state.next();
            if (is_escapable_character(next)) {
                const char *escape_char = escape_character(next);
                state.write(escape_char);
                state.ignore_n(2);
                break;
            }

            state.write_n(2);
            break;
        }

        // Code spans
        case backstick: {
            if (state.in_code_span) {
                sz_t backsticks_count = state.count_ocurrences(backstick);

                // Check if the span can be closed
                if (backsticks_count == state.number_of_backsticks) {
                    // Close the span
                    state.ignore_n(backsticks_count);
                    state.write("</code>");
                    state.in_code_span = false;
                    break;
                }

                // Leave it open for the next
                state.write_n(backsticks_count);
                break;
            }

            // Open the span
            sz_t backsticks_count = state.count_ocurrences('`');
            state.number_of_backsticks = backsticks_count;
            state.ignore_n(backsticks_count);
            state.write("<code>");
            state.in_code_span = true;
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
            state.write_n(1);
            break;
        }
        }
    }

    return state.result.str();
}

static bool is_escapable_character(char c) noexcept {
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

static const char* escape_character(char c) noexcept {
    switch (c) {
    case '\\':
        return "&bsol;";
    case '\'':
        return "&apos;";
    case '!':
        return "&excl;";
    case '"':
        return "&quot;";
    case '#':
        return "&num;";
    case '$':
        return "&dollar;";
    case '%':
        return "&percnt;";
    case '&':
        return "&amp;";
    case '(':
        return "&lpar;";
    case ')':
        return "&rpar;";
    case '*':
        return "&ast;";
    case '+':
        return "&plus;";
    case ',':
        return "&comma;";
    case '-':
        return "-"; // TODO(Pablo)
    case '.':
        return "&period;";
    case '/':
        return "&sol;";
    case ':':
        return "&colon;";
    case ';':
        return "&semi;";
    case '<':
        return "&lt;";
    case '=':
        return "&equals;";
    case '>':
        return "&gt;";
    case '?':
        return "&quest;";
    case '@':
        return "&commat;";
    case '[':
        return "&lsqb;";
    case ']':
        return "&rsqb;";
    case '^':
        return "&Hat;";
    case '_':
        return "&lowbar;";
    case '`':
        return "&grave;";
    case '{':
        return "&lcub;";
    case '|':
        return "&verbar;";
    case '}':
        return "&rcub;";
    case '~':
        return "~"; // TODO(Pablo)
    default:
        return "NOT AN ESCAPE CHARATER YOU !#$%&";
    }

}

} // namespace cmm
