#ifndef CMD_HPP
#define CMD_HPP

#include <iostream>
#include <fstream>

constexpr const char *help_message = R"(
cmm++
=====

Flags
-----

    --debug-messages     (-d) Habilitar mensajes de debug
    --input-file [File]  (-f) Archivo de entrada
    --output-file [File] (-o) Archivo de salida
    --help               (-h) Muestra este mensaje
)";


namespace imp {

extern std::istream *in_stream;              // NOLINT
extern std::ostream *out_stream;             // NOLINT
extern std::ifstream possible_input_stream;  // NOLINT
extern std::ofstream possible_output_stream; // NOLINT

} // namespace imp

class missing_cmdline_args : public std::exception {
   public:
    [[nodiscard]] const char *what() const override;
};

extern bool just_help_message; // NOLINT

// NOLINTNEXTLINE
void parce_cmd_args(int argc, char *argv[]);

std::istream &get_input_stream(void);
std::ostream &get_out_stream(void);

#endif
