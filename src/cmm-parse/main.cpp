#include <iostream>
#include <cmm/cmm.hpp>

#include "cmd.hpp"

int main(int argc, char *argv[]) {
    try {
        parce_cmd_args(argc, argv);
    } catch (const missing_cmdline_args &e) {
        std::cerr << e.what() << '\n';
        return 1;
    }

    cmm::log << "---- Debug messages enabled ----\n";

    try {

        std::ostream &out = get_out_stream();
        std::istream &in = get_input_stream();

        if (just_help_message) {
            out << help_message << '\n';
            return 0;
        }

        std::string source = cmm::full_stream_read(in);

        out << cmm::parce(source);
        return 0;

    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
        return 1;
    }
}
