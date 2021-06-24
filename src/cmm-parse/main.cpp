#include <cassert>
#include <iostream>
#include <cmm/cmm.hpp>

#include "cmd.hpp"

constexpr bool debug_inlines = false;
constexpr bool debug_blocks = true;


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

        if constexpr (debug_inlines) {
            out << cmm::process_inlines(source);

        } else if constexpr (debug_blocks) {
            auto blocks = cmm::separate_blocks(source);
            for (const auto &b : blocks) {
                out << "------------ Found block ----------------\n";
                out << b << "(BLOCK_END)\n";
                out << "Type: " << cmm::describe(cmm::identify_block_type(b))
                    << '\n';
                out << "-----------------------------------------\n";
            }

        } else {
            // Normal parsing
            out << cmm::parce(source);
        }
        return 0;

    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
        return 1;
    }
}
