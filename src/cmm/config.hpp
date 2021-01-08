#ifndef CMM_CONFIG_HPP
#define CMM_CONFIG_HPP

#include <iostream>
#include <ostream>

namespace cmm::config {

namespace imp {

extern std::istream *in_stream;              // NOLINT
extern std::ostream *out_stream;             // NOLINT
extern std::ifstream possible_input_stream;  // NOLINT
extern std::ofstream possible_output_stream; // NOLINT

} // namespace imp

constexpr const char *help_message = "Ayuda";

/// Configures the parcer
void parce_cmd_args(int argc, char *argv[]); // NOLINT

std::istream &get_input_stream(void);
std::ostream &get_out_stream(void);

constexpr bool debug_enabled = true;
constexpr bool inlines_with_regex = false;

extern bool debug;             // NOLINT
extern bool just_help_message; // NOLINT

class missing_cmdline_args : public std::exception {
   public:
    [[nodiscard]] const char *what() const override;
};

} // namespace cmm::config

#endif
