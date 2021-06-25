#ifndef CMM_SYNTAX_ERROR_HPP
#define CMM_SYNTAX_ERROR_HPP

#include <string>
#include <exception>

namespace cmm {

class syntax_error : public std::exception {
   public:
    explicit syntax_error(std::string message);
    [[nodiscard]] const char *what() const noexcept override;
   private:
    std::string m = "Syntax Error";
};

} // namespace cmm

#endif
