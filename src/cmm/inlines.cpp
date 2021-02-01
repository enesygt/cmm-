#include <cmm/inlines.hpp>
#include <cmm/logger.hpp>
#include <cmm/escape_chars.hpp>

#include "_private/inline_state.hpp"

namespace cmm {

constexpr char escape_char = '\\';
constexpr char backstick = '`';

static void open_span(imp::inline_state* s);
static void close_span(imp::inline_state* s, sz_t backsticks_count);
static inline bool span_can_be_closed(imp::inline_state *s,
                                      sz_t               backsticks_count);

std::string process_inlines(const std::string &source) {
    std::stringstream result;
    sz_t              index = 0;

    imp::inline_state state = {source, result, index};

    /*
     * We will go character by character, acting acording to the state for the
     * code spans, emphasis, and strong emphasis.
     *
     * The links and images will be treated inline
     */
    while (state.is_valid()) {
        switch (state.current()) {

        // ----------------------Backslash escapes ----------------------
        case escape_char: {
            if (!state.next_is_in_range()) {
                state.write_n(1);
                break;
            }

            char next = state.next();
            if (is_escapable_character(next)) {
                const char *escaped_char = escape_character(next);
                state.write(escaped_char);
                state.ignore_n(2);
                break;
            }

            state.write_n(2);
            break;
        }

        // ---------------------- Code Spans ----------------------
        case backstick: {
            if (state.in_code_span) {
                sz_t backsticks_count = state.count_ocurrences(backstick);

                if (span_can_be_closed(&state, backsticks_count)) {
                    close_span(&state, backsticks_count);
                    break;
                }

                // Leave it open for the next
                state.write_n(backsticks_count);
                break;
            }

            open_span(&state);
            break;
        }

        // ---------------------- Emphasis and Strong ----------------------
        case '*':
        case '_': {
            if (state.in_emphasis) {

                break;
            }
            if (state.in_strong_emphasis) {

                break;
            }
            sz_t ocurrences = state.count_ocurrences(state.current());
            if (ocurrences == 1) {
                break;
            }
            if (ocurrences == 2)
            break;
        }

        // ---------------------- Links ----------------------
        case '[': {

            break;
        }

        // ---------------------- Images ----------------------
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

static inline bool span_can_be_closed(imp::inline_state*s, sz_t backsticks_count) {
    return backsticks_count == s->number_of_backsticks;
}

static void open_span(imp::inline_state *s) {
    sz_t backsticks_count = s->count_ocurrences('`');
    s->number_of_backsticks = backsticks_count;
    s->ignore_n(backsticks_count);
    s->write("<code>");
    s->in_code_span = true;
}

static void close_span(imp::inline_state* s, sz_t backsticks_count) {
    s->ignore_n(backsticks_count);
    s->write("</code>");
    s->in_code_span = false;
}

} // namespace cmm
