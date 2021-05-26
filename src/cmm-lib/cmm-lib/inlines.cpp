#include <cmm/inlines.hpp>
#include <cmm/logger.hpp>
#include <cmm/escape_chars.hpp>

#include "_private/inline_state.hpp"

namespace cmm {

constexpr char escape_char = '\\';
constexpr char backstick = '`';

namespace {

void escape_if_needed(imp::inline_state *s);
void process_code_spans(imp::inline_state *s);
void process_emphasis_and_strong_emphasis(imp::inline_state *s);
void process_links(imp::inline_state *s);

} // namespace

std::string process_inlines(const std::string &source) {
    std::stringstream result;
    size_t              index = 0;

    imp::inline_state state = {source, result, index};

    /*
     * We will go character by character, acting acording to the state for the
     * code spans, emphasis, and strong emphasis.
     *
     * The links and images will be treated directly
     */
    while (state.is_valid()) {
        switch (state.current()) {

        // ----------------------Backslash escapes ----------------------
        case escape_char: {
            escape_if_needed(&state);
            break;
        }

        // ---------------------- Code Spans ----------------------
        case backstick: {
            process_code_spans(&state);
            break;
        }

        // ---------------------- Emphasis and Strong ----------------------
        case '*': {
            process_emphasis_and_strong_emphasis(&state);
            break;
        }

        // ---------------------- Links ----------------------
        case '[': {
            process_links(&state);
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

namespace {

// Span utils
void open_span(imp::inline_state *s);
void close_span(imp::inline_state *s, size_t backsticks_count);
bool span_can_be_closed(imp::inline_state *s, size_t backsticks_count);

// Emphasis utils
bool is_strong_emphasis(const imp::inline_state &s);
void open_emphasis(imp::inline_state *s);
void close_emphasis(imp::inline_state *s);
void open_strong_emphasis(imp::inline_state *s);
void close_strong_emphasis(imp::inline_state *s);

// Links util
struct link_positions {

};

void escape_if_needed(imp::inline_state *s) {
    if (!s->next_is_in_range()) {
        s->write_n(1);
        return;
    }

    const char next = s->next();
    if (is_escapable_character(next)) {
        const char *escaped_char = escape_character(next);
        s->write(escaped_char);
        s->ignore_n(2);
        return;
    }

    s->write_n(2);
}

void process_code_spans(imp::inline_state *s) {
    if (s->in_code_span) {
        size_t backsticks_count = s->count_ocurrences(backstick);

        if (span_can_be_closed(s, backsticks_count)) {
            close_span(s, backsticks_count);
            return;
        }

        // Leave it open for the next
        s->write_n(backsticks_count);
        return;
    }

    open_span(s);
}

void process_emphasis_and_strong_emphasis(imp::inline_state *s) {
    const bool indicates_strong_emphasis = is_strong_emphasis(*s);
    const size_t count = s->count_ocurrences(s->current());

    if (s->in_emphasis && (!indicates_strong_emphasis || count == 3)) {
        close_emphasis(s);
        return;
    }

    if (s->in_strong_emphasis && indicates_strong_emphasis) {
        close_strong_emphasis(s);
        return;
    }

    if (indicates_strong_emphasis) {
        open_strong_emphasis(s);
        return;
    }

    // Normal emphasis
    open_emphasis(s);
}

void process_links(imp::inline_state *s) {

}

bool span_can_be_closed(imp::inline_state *s, size_t backsticks_count) {
    return backsticks_count == s->number_of_backsticks;
}

void open_span(imp::inline_state *s) {
    size_t backsticks_count = s->count_ocurrences('`');
    s->number_of_backsticks = backsticks_count;
    s->ignore_n(backsticks_count);
    s->write("<code>");
    s->in_code_span = true;
}

void close_span(imp::inline_state *s, size_t backsticks_count) {
    s->ignore_n(backsticks_count);
    s->write("</code>");
    s->in_code_span = false;
}

bool is_strong_emphasis(const imp::inline_state &s) {
    if (!s.next_is_in_range()) {
        return false;
    }
    return s.current() == s.next();
}

void open_emphasis(imp::inline_state *s) {
    s->ignore_n(1);
    s->write("<em>");
    s->in_emphasis = true;
}

void close_emphasis(imp::inline_state *s) {
    s->ignore_n(1);
    s->write("</em>");
    s->in_emphasis = false;
}

void open_strong_emphasis(imp::inline_state *s) {
    s->ignore_n(2);
    s->write("<strong>");
    s->in_strong_emphasis = true;
}

void close_strong_emphasis(imp::inline_state *s) {
    s->ignore_n(2);
    s->write("</strong>");
    s->in_strong_emphasis = false;
}

} // namespace

} // namespace cmm
