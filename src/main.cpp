#include <iostream>
#include <cmm/cmm.hpp>

int main(int argc, char *argv[]) {
    try {
        cmm::config::parce_cmd_args(argc, argv);
    } catch (const cmm::config::missing_cmdline_args &e) {
        std::cerr << e.what() << '\n';
        return 1;
    }

    cmm::log << "---- Debug messages enabled ----\n";

    try {

        std::ostream &out = cmm::config::get_out_stream();
        std::istream &in = cmm::config::get_input_stream();

        if (cmm::config::just_help_message) {
            out << cmm::config::help_message << '\n';
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
