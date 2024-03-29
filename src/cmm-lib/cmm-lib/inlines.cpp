#include <optional>
#include <cassert>
#include <string_view>

#include <cmm/logger.hpp>
#include <cmm/inlines.hpp>
#include <cmm/escape_chars.hpp>

#include "_private/inline_state.hpp"

constexpr char escape_char = '\\';
constexpr char backstick = '`';

using cmm::imp::inline_state;
using cmm::is_escapable_character;
using cmm::escape_character;

static void escape_if_needed(inline_state *s);
static void process_code_spans(inline_state *s);
static void process_emphasis_and_strong_emphasis(inline_state *s);
static void process_links(inline_state *s);
static void process_images(inline_state *s);

std::string cmm::process_inlines(const std::string &source) {
    std::stringstream result;
    size_t            i = 0;

    inline_state state = {source, result, i};

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
            process_images(&state);
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


// Span utils
static void open_span(inline_state *s);
static void close_span(inline_state *s, size_t backsticks_count);
static bool span_can_be_closed(inline_state *s, size_t backsticks_count);


// Emphasis utils
static bool is_strong_emphasis(const inline_state &s);
static void open_emphasis(inline_state *s);
static void close_emphasis(inline_state *s);
static void open_strong_emphasis(inline_state *s);
static void close_strong_emphasis(inline_state *s);


// Links and images utils
struct link_positions {
    size_t total_length = 0;
    size_t name_length = 0;
    size_t url_legth = 0;
    size_t title_length = 0;
};

struct link_debug_data {
    std::string    link_text;
    link_positions positions;
};


// static std::ostream &operator<<(std::ostream &o, const link_debug_data &l);
static std::optional<link_positions> check_if_valid_link(inline_state *s);

static std::string get_link_name(std::stringstream &   source,
                                 const link_positions &positions);
static std::string get_link_url(std::stringstream &   source,
                                const link_positions &positions);
static std::string get_link_title(std::stringstream &   source,
                                  const link_positions &positions);


static void escape_if_needed(inline_state *s) {
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

static void process_code_spans(inline_state *s) {
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

static void process_emphasis_and_strong_emphasis(inline_state *s) {

    const bool   indicates_strong_emphasis = is_strong_emphasis(*s);
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

static void process_links(inline_state *s) {

    const std::optional<link_positions> positions = check_if_valid_link(s);
    if (!positions) {
        s->write_n(1);
        return;
    }

    const std::string link_text =
        s->source.substr(s->index, positions->total_length);

    std::stringstream ss(link_text);

    std::string link_name = get_link_name(ss, positions.value());

    // Inside the [] there could be more markdown, so lets process that too.
    link_name = cmm::process_inlines(link_name);

    const std::string link_url = get_link_url(ss, positions.value());
    const std::string link_title = get_link_title(ss, positions.value());

    s->ignore_n(positions->total_length);
    s->write("<a href=\"");
    s->write(link_url.c_str());
    s->write("\" title=\"");
    s->write(link_title.c_str());
    s->write("\">");
    s->write(link_name.c_str());
    s->write("</a>");
}

static void process_images(inline_state *s) {
    if (!s->next_is_in_range()) {
        s->write_n(1);
        return;
    }

    if (s->next() != '[') {
        s->write_n(1);
        return;
    }

    // Ignore the ! so we can get the data as if it as a link
    s->ignore_n(1);

    const std::optional<link_positions> positions = check_if_valid_link(s);

    if (!positions) {
        s->write("!");
        return;
    }

    std::string image_text =
        s->source.substr(s->index, positions->total_length);
    std::stringstream ss(image_text);

    const std::string image_name = get_link_name(ss, positions.value());
    const std::string image_url = get_link_url(ss, positions.value());
    const std::string image_title = get_link_title(ss, positions.value());

    s->ignore_n(positions->total_length);
    s->write("<img src=\"");
    s->write(image_url.c_str());
    s->write("\" alt=\"");
    s->write(image_name.c_str());
    s->write("\" title=\"");
    s->write(image_title.c_str());
    s->write("\"/>");
}

static bool span_can_be_closed(inline_state *s, size_t backsticks_count) {
    return backsticks_count == s->number_of_backsticks;
}

static void open_span(inline_state *s) {
    size_t backsticks_count = s->count_ocurrences('`');
    s->number_of_backsticks = backsticks_count;
    s->ignore_n(backsticks_count);
    s->write("<code>");
    s->in_code_span = true;
}

static void close_span(inline_state *s, size_t backsticks_count) {
    s->ignore_n(backsticks_count);
    s->write("</code>");
    s->in_code_span = false;
}

static bool is_strong_emphasis(const inline_state &s) {
    if (!s.next_is_in_range()) {
        return false;
    }
    return s.current() == s.next();
}

static void open_emphasis(inline_state *s) {
    s->ignore_n(1);
    s->write("<em>");
    s->in_emphasis = true;
}

static void close_emphasis(inline_state *s) {
    s->ignore_n(1);
    s->write("</em>");
    s->in_emphasis = false;
}

static void open_strong_emphasis(inline_state *s) {
    s->ignore_n(2);
    s->write("<strong>");
    s->in_strong_emphasis = true;
}

static void close_strong_emphasis(inline_state *s) {
    s->ignore_n(2);
    s->write("</strong>");
    s->in_strong_emphasis = false;
}

static std::optional<link_positions> check_if_valid_link(inline_state *s) {
    constexpr size_t character_not_found = inline_state::character_not_found;

    link_positions positions;

    /*
     * Fail conditions:
     *
     *  * There is no closing ]
     *  * The character next to the ] is not a (
     *  * There is no closing )
     *
     */

    size_t link_section_closing = s->distance_to(']');
    if (link_section_closing == character_not_found) {
        return std::nullopt;
    }

    if (s->at(link_section_closing + 1) != '(') {
        return std::nullopt;
    }

    size_t title_section_closing = s->distance_to(')');
    if (title_section_closing == character_not_found) {
        return std::nullopt;
    }

    auto has_title = [&]() -> bool {
        const auto to_space = s->distance_to(' ', link_section_closing);
        return (to_space != character_not_found
                && to_space < s->distance_to(')', link_section_closing));
    };

    /*
     *  So our link looks like:
     *
     *      [ l i n k ] ( / u r l   t i t l e )
     *      0 1 2 3 4 5 6 7 8 9 ...           17
     *                ^                       ^
     *                |                       |
     *                |                       |
     *       link_section_closing             |
     *                                        |
     *                            url_title_section_closing
     *
     *
     * So:
     *
     *      * The name length is link_section_closing - 1
     *      * The url length will be from the '(' to the next ' ' - 1
     *      * The title lenght is the total lenght minus the name and url
     *        lengths, minus the '[', ']', '(', ' ', ')' (-5).
     *
     * Applies the same to the image (We are ommiting the ! at the start).
     */

    positions.total_length = title_section_closing + 1;
    positions.name_length = link_section_closing - 1;

    if (has_title()) {
        positions.url_legth = s->distance_to(' ', link_section_closing + 1) - 1;
        positions.title_length = positions.total_length - positions.name_length
                                 - positions.url_legth
                                 - 5; // NOLINT -5 explained in comment above

    } else {
        // For the case where we have no link apply the same logic as above
        positions.title_length = 0;
        positions.url_legth =
            positions.total_length - positions.name_length - 4;
    }


    return positions;
}

#if 0

// This code stays here for debuging purposes

std::ostream &operator<<(std::ostream &o, const link_debug_data &l) {

    o << "\nFound link: '" << l.link_text << "'\n";
    o << "Link Data: " << '\n';
    o << "\t Total length: " << l.positions.total_length << '\n';
    o << "\t Name length: " << l.positions.name_length << '\n';
    o << "\t Url length: " << l.positions.url_legth << '\n';
    o << "\t Title length: " << l.positions.title_length << '\n';

    return o;
}

#endif

static std::string get_link_name(std::stringstream &   source,
                                 const link_positions &positions) {

    // Ignore the opening [
    source.ignore();

    // Read the name
    std::string link_name(positions.name_length + 1, '\0');
    if (!source.read(link_name.data(),
                     static_cast<std::streamsize>(positions.name_length))) {
        throw std::runtime_error("Unable to read link name");
    }
    return link_name;
}

static std::string get_link_url(std::stringstream &   source,
                                const link_positions &positions) {

    // Ignore the ](
    source.ignore(2);

    // Read the url
    std::string link_url(positions.url_legth + 1, '\0');
    if (!source.read(link_url.data(),
                     static_cast<std::streamsize>(positions.url_legth))) {
        throw std::runtime_error("Unable to read link url");
    }
    return link_url;
}

static std::string get_link_title(std::stringstream &   source,
                                  const link_positions &positions) {

    std::string link_title;
    if (positions.title_length != 0) {
        // Ignore the ' '
        source.ignore();

        link_title = std::string(positions.title_length + 1, '\0');
        if (!source.read(
                link_title.data(),
                static_cast<std::streamsize>(positions.title_length))) {
            throw std::runtime_error("Unable to read link url");
        }
    }
    return link_title;
}
