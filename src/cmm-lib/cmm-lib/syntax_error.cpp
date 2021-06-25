#include <cmm/syntax_error.hpp>
#include <utility>

using cmm::syntax_error;


syntax_error::syntax_error(std::string message) : m(std::move(message)) {}


[[nodiscard]] const char *syntax_error::what() const noexcept {
    return m.c_str();
}
