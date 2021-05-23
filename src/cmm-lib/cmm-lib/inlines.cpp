#include <cmm/inlines.hpp>
#include <cmm/logger.hpp>
#include <cmm/escape_chars.hpp>

#include "_private/inline_state.hpp"

namespace cmm {

constexpr char escape_char = '\\';
constexpr char backstick = '`';

// Span
static inline void open_span(imp::inline_state* s);
static inline void close_span(imp::inline_state* s, sz_t backsticks_count);
static inline bool span_can_be_closed(imp::inline_state *s,
                                      sz_t               backsticks_count);

// Emphasis
static inline bool is_strong_emphasis(const imp::inline_state& s);
static inline void open_emphasis(imp::inline_state* s);
static inline void close_emphasis(imp::inline_state* s);
static inline void open_strong_emphasis(imp::inline_state* s);
static inline void close_strong_emphasis(imp::inline_state* s);

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
        case '*': {
            const bool indicates_strong_emphasis = is_strong_emphasis(state);
            const sz_t count = state.count_ocurrences(state.current());

            if (state.in_emphasis
                && (!indicates_strong_emphasis || count == 3)) {
                close_emphasis(&state);
                break;
            }

            if (state.in_strong_emphasis && indicates_strong_emphasis) {
                close_strong_emphasis(&state);
                break;
            }

            if (indicates_strong_emphasis) {
                open_strong_emphasis(&state);
                break;
            }

            // Normal emphasis
            open_emphasis(&state);
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

static inline void open_span(imp::inline_state *s) {
    sz_t backsticks_count = s->count_ocurrences('`');
    s->number_of_backsticks = backsticks_count;
    s->ignore_n(backsticks_count);
    s->write("<code>");
    s->in_code_span = true;
}

static inline void close_span(imp::inline_state* s, sz_t backsticks_count) {
    s->ignore_n(backsticks_count);
    s->write("</code>");
    s->in_code_span = false;
}

static inline bool is_strong_emphasis(const imp::inline_state& s) {
    if (!s.next_is_in_range()) {
        return false;
    }
    return s.current() == s.next();
}

static inline void open_emphasis(imp::inline_state* s) {
    s->ignore_n(1);
    s->write("<em>");
    s->in_emphasis = true;
}

static inline void close_emphasis(imp::inline_state* s) {
    s->ignore_n(1);
    s->write("</em>");
    s->in_emphasis = false;
}

static inline void open_strong_emphasis(imp::inline_state *s) {
    s->ignore_n(2);
    s->write("<strong>");
    s->in_strong_emphasis = true;
}

static inline void close_strong_emphasis(imp::inline_state* s) {
    s->ignore_n(2);
    s->write("</strong>");
    s->in_strong_emphasis = false;
}

} // namespace cmm
