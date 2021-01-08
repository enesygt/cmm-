#include <cmm/inlines.hpp>
#include <cassert>
#include <sstream>
#include <regex>

namespace cmm {

constexpr char escape_char = '\\';

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

inline static void process_strong_emphasis_manual(std::string &source) {
    using str_it = std::string::iterator;

    constexpr size_t inmediate_or_not_found = 0;

    auto lenght_to_closing =
        [](str_it current, str_it end, char closer, char delimiter) -> size_t {

        for (auto i = current; i != end; i++) {
            if (*i == delimiter) {
                return inmediate_or_not_found;
            }
            if (*i == closer and *std::next(i) == closer) {
                str_it::difference_type distance = i - current - 1;
                assert(distance >= 0);
                return distance;
            }
        }
        return inmediate_or_not_found;
    };

    std::stringstream result;
    auto write_n = [&](str_it iter, size_t n) -> void {
        for (size_t i = 0; i < n; i++) {
            result << *(iter++);
        }
    };

    str_it i = source.begin();
    const str_it end = source.end();

    auto ignore_n = [&](size_t n) {
        i += n;
    };

    for (; i != end; ++i) {
        switch (*i) {
        case escape_char: {
            auto next = std::next(i);
            // If the next character denotes emphasis, ignore it
            if (*next == '*' or *next == '_') {
                result << *i << *next;
            ++i;
            } else {
                result << escape_char;
            }
            break;
        }

        case '_':
        case '*': {
            // If you dont allow multiline emphasis, change delimiter to \n
            size_t lenght = lenght_to_closing(std::next(i), end, *i, '\0');
            if (lenght != inmediate_or_not_found) {
                ignore_n(2);
                result << "<strong>";
                write_n(i, lenght);
                result << "</strong>";
                ignore_n(2);
            }
            break;
        }

        default:
            result >> *i;
        }
    }

    source = result.str();
}

void process_strong_emphasis(std::string &source) {
    if (config::inlines_with_regex) {
        process_strong_emphasis_regex(source);
    } else {
        process_strong_emphasis_manual(source);
    }
}

inline static void process_emphasis_regex(std::string &source) {
    std::regex  emphasis(R"(([^\\_*]*)[_*]([^_*]*[^_*\\])[_*])");
    std::string replacement("$1<em>$2</em>$3");

    std::string result = std::regex_replace(source, emphasis, replacement);

    source = std::move(result);
}

void process_emphasis(std::string &source) {
    process_emphasis_regex(source);
}

void process_code_spans(std::string &source) {}

void process_links(std::string &source) {}

void process_images(std::string &source) {}

} // namespace cmm
