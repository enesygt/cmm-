#include <cmm/config.hpp>

#include <fstream>
#include <cstring>

namespace cmm::config {

namespace imp {

std::istream *in_stream = &std::cin;   // NOLINT
std::ostream *out_stream = &std::cout; // NOLINT
std::ifstream possible_input_stream;   // NOLINT
std::ofstream possible_output_stream;  // NOLINT

} // namespace imp

bool debug = false;              // NOLINT
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
        if (std::strcmp("-d", argv_at(i)) == 0
            || std::strcmp("--debug-messages", argv_at(i)) == 0) {

            debug = true;
        }

        // Input file
        else if (std::strcmp("-f", argv_at(i)) == 0
                 || std::strcmp("--input-file", argv_at(i)) == 0) {

            const char *in = argv_at(i + 1);
            // Do nothing if stream is stdin
            if (std::strcmp("-", in) != 0) {
                imp::possible_input_stream.open(argv_at(i + 1));
                imp::in_stream = &imp::possible_input_stream;
            }
        }

        // Output file
        else if (std::strcmp("-o", argv_at(i)) == 0
                 || std::strcmp("--output-file", argv_at(i)) == 0) {

            const char *out = argv_at(i + 1);
            // Do nothing if stream is stdout
            if (std::strcmp("-", out) != 0) {
                imp::possible_output_stream.open(argv_at(i + 1));
                imp::out_stream = &imp::possible_output_stream;
            }
        }

        // Help message
        else if (std::strcmp("-h", argv_at(i)) == 0
                 || std::strcmp("--help", argv_at(i)) == 0) {
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

const char *missing_cmdline_args::what() const {
    return "Missing comand line arguments";
}

} // namespace cmm::config
