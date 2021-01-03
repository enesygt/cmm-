#ifndef CMM_CONFIG_HPP
#define CMM_CONFIG_HPP

#include <iostream>
#include <ostream>

namespace cmm {
namespace config {

namespace imp {

extern std::istream *in_stream;              // NOLINT
extern std::ostream *out_stream;             // NOLINT
extern std::ifstream possible_input_stream;  // NOLINT
extern std::ofstream possible_output_stream; // NOLINT

} // namespace imp

constexpr const char *help_message = "Ayuda";

// NOLINTNEXTLINE
void parce_cmd_args(int argc, char *argv[]);

std::istream &get_input_stream(void);
std::ostream &get_out_stream(void);

constexpr bool debug_enabled = true;

extern bool debug;             // NOLINT
extern bool just_help_message; // NOLINT

} // namespace config
} // namespace cmm

#endif
