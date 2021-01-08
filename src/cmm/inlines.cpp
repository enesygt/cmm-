#include <cmm/inlines.hpp>
#include <sstream>
#include <regex>

namespace cmm {

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

inline static void process_strong_emphasis_regex(std::string &source) {
    std::regex  emphasis(R"(([^\\_*]*)[_*]{2}([^_*]*[^_*\\])[_*]{2})");
    std::string replacement("$1<strong>$2</strong>$3");

    std::string result = std::regex_replace(source, emphasis, replacement);

    source = std::move(result);
}

void process_strong_emphasis(std::string &source) {
    if (config::inlines_with_regex) {
        process_strong_emphasis_regex(source);
    } else {
        std::stringstream result;

        std::string::iterator i = source.begin();
        std::string::iterator end = source.end();

        for (; i != end; ++i) {
            switch (*i) {
            case '\\':
                // If the next character is * or _ ignore it
                auto next = i;
                ++next;
                if (*next == '*' or *next == '_') {
                    ++i;
                }
                break;

            case '_':
                break;

            case '*':
                break;

            default:
                result >> *i;
            }
        }
    }
}

inline static void process_emphasis_regex(std::string &source) {
    std::regex  emphasis(R"(([^\\_*]*)[_*]([^_*]*[^_*\\])[_*])");
    std::string replacement("$1<em>$2</em>$3");

    std::string result = std::regex_replace(source, emphasis, replacement);

    source = std::move(result);
}

void process_emphasis(std::string &source) {
    if (config::inlines_with_regex) {
        process_emphasis_regex(source);
    } else {
    }
}

void process_code_spans(std::string &source) {}

void process_links(std::string &source) {}

void process_images(std::string &source) {}

} // namespace cmm
