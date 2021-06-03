/*
 * NOTE:
 *
 * This file is meant to only be used with "src/cmm-lib/cmm-lib/inlines.cpp",
 * nothing more
 *
 * */

#ifndef CMM_PRIVATE_INLINE_STATE
#define CMM_PRIVATE_INLINE_STATE

#include <cmm/usings.hpp>
#include <cassert>
#include <string>
#include <sstream>
#include <cstddef>

namespace cmm::imp {

namespace { // NOLINT

struct inline_state final {
    const std::string &source; // NOLINT
    std::stringstream &result; // NOLINT
    cmm::index &       index;  // NOLINT

    // Code spans
    bool       in_code_span = false;     // NOLINT
    cmm::index number_of_backsticks = 0; // NOLINT

    // Emphasis
    bool in_emphasis = false; // NOLINT

    // Strong emphasis
    bool in_strong_emphasis = false; // NOLINT

    [[nodiscard]] bool is_valid(void) const {
        return index < source.size();
    }

    // Returns the current character
    [[nodiscard]] char current(void) const noexcept {
        assert(this->is_valid());
        return source[index];
    }

    // Returns the next character
    [[nodiscard]] char next(void) const noexcept {
        assert(this->next_is_in_range());
        return source[index + 1];
    }

    [[nodiscard]] bool next_is_in_range(void) const noexcept {
        return (index + 1) < source.size();
    };

    // Writes n characters to the result
    void write_n(cmm::index n) {
        for (cmm::index i = 0; i < n; i++) {
            assert(this->is_valid());
            result << source[index++];
        }
    };

    // Writes str to the result
    void write(const char *const str) {
        result << str;
    }

    void ignore_n(cmm::index n) noexcept {
        index += n;
    };

    // Counts the times a character is found, from the current position in the
    // source
    [[nodiscard]] cmm::index count_ocurrences(char c) const noexcept {
        cmm::index count = 0;
        while (source[index + count] == c) {
            ++count;
        }
        return count;
    }

    constexpr static cmm::index character_not_found = -1;

    // Counts the amount of characters til c apears. Will start advance
    // characters from the current character.
    [[nodiscard]] cmm::index
        distance_to(char c, cmm::index advance = 0) const noexcept {

        const cmm::index starting_position = index + advance;
        cmm::index       distance = 0;

        while (source[starting_position + distance]) {
            if (source[starting_position + distance] == c) {
                return distance;
            }
            ++distance;
        }

        return character_not_found;
    }

    // Will return the character, `position`characters from the current position
    [[nodiscard]] char at(cmm::index position) const noexcept {
        return source[index + position];
    }
};

} // namespace
} // namespace cmm::imp

#endif
