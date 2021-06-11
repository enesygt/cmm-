#ifndef CMM_ESCAPE_CHARS_HPP
#define CMM_ESCAPE_CHARS_HPP

namespace cmm {

/**
 * @return true if `c` can be escaped
 */
bool is_escapable_character(char c) noexcept;

/**
 * @return The html representation of `c`
 */
const char *escape_character(char c) noexcept;

} // namespace cmm

#endif
