#ifndef CMM_ESCAPE_CHARS_HPP
#define CMM_ESCAPE_CHARS_HPP

namespace cmm {

bool        is_escapable_character(char c) noexcept;
const char *escape_character(char c) noexcept;

}

#endif
