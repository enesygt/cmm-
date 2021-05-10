#include <cstring>

#include <cmm/config.hpp>

#include "cmd.hpp"

namespace imp {

std::istream *in_stream = &std::cin;   // NOLINT
std::ostream *out_stream = &std::cout; // NOLINT
std::ifstream possible_input_stream;   // NOLINT
std::ofstream possible_output_stream;  // NOLINT

} // namespace imp

bool just_help_message = false;  // NOLINT

// NOLINTNEXTLINE
void parce_cmd_args(int argc, char *argv[]) {
    // Secure argv access
    auto argv_at = [&](int position) -> char * {
        if (position < argc) {
            return argv[position]; // NOLINT
        }
        throw missing_cmdline_args{};
    };

    for (int i = 0; i < argc; i++) {
        // Debug messages
        if (strcmp("-d", argv_at(i)) == 0
            || strcmp("--debug-messages", argv_at(i)) == 0) {

            cmm::config::conf.debug(true);
        }

        // Input file
        else if (strcmp("-f", argv_at(i)) == 0
                 || strcmp("--input-file", argv_at(i)) == 0) {

            const char *in = argv_at(i + 1);
            // Do nothing if stream is stdin
            if (strcmp("-", in) != 0) {
                imp::possible_input_stream.open(argv_at(i + 1));
                imp::in_stream = &imp::possible_input_stream;
            }
        }

        // Output file
        else if (strcmp("-o", argv_at(i)) == 0
                 || strcmp("--output-file", argv_at(i)) == 0) {

            const char *out = argv_at(i + 1);
            // Do nothing if stream is stdout
            if (strcmp("-", out) != 0) {
                imp::possible_output_stream.open(argv_at(i + 1));
                imp::out_stream = &imp::possible_output_stream;
            }
        }

        // Help message
        else if (strcmp("-h", argv_at(i)) == 0
                 || strcmp("--help", argv_at(i)) == 0) {
            just_help_message = true;
            return;
        }
    }
}

std::istream &get_input_stream(void) {
    return *imp::in_stream;
}

std::ostream &get_out_stream(void) {
    return *imp::out_stream;
}

const char *missing_cmdline_args::what() const noexcept {
    return "Missing comand line arguments";
}
