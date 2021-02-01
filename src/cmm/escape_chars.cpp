#include <cmm/escape_chars.hpp>

namespace cmm {

bool is_escapable_character(char c) noexcept {
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

const char *escape_character(char c) noexcept {
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
