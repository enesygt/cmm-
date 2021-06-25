#include <cmm/text_block.hpp>

#include "catch2/catch.hpp"

// The cognitive complexity is due to the expansion of the catch2
// macros
//
// So: NOLINTNEXTLINE
TEST_CASE("cmm::separate_blocks", "[text_block]") {
    SECTION("Solves the optimal case") {
        const std::string source =
            "Hola\n"
            "\n"
            "Este tendria que ser un bloque\n"
            "para ser separado\n"
            "\n"
            "Y este seria el segundo bloque a identificar\n";

        // clang-format off
        const std::vector<cmm::text_block> expected_result = {
            {
                std::string("Hola\n")
            },
            {
                std::string("Este tendria que ser un bloque\n"),
                std::string("para ser separado\n")
            },
            {
                std::string("Y este seria el segundo bloque a identificar\n")
            }
        };
        // clang-format on

        const std::vector<cmm::text_block> result =
            cmm::separate_blocks(source);

        CHECK(result == expected_result);
    }

    SECTION("Empy vector if no blocks where found") {
        const std::string source{};
        const std::vector<cmm::text_block> expected_result;

        const std::vector<cmm::text_block> result =
            cmm::separate_blocks(source);

        CHECK(result == expected_result);
    }

    SECTION("Manages single block") {
        const std::string source = "Hola\n";
        const std::vector<cmm::text_block> expected_result = {
            {
                std::string("Hola\n")
            }
        };

        const std::vector<cmm::text_block> result =
            cmm::separate_blocks(source);

        CHECK(result == expected_result);
    }

    SECTION("No '\\n' at the end of the last block") {
        const std::string source =
            "Hola\n"
            "\n"
            "Este tendria que ser un bloque\n"
            "para ser separado\n"
            "\n"
            "Y este seria el segundo bloque a identificar";

        // clang-format off
        const std::vector<cmm::text_block> expected_result = {
            {
                std::string("Hola\n")
            },
            {
                std::string("Este tendria que ser un bloque\n"),
                std::string("para ser separado\n")
            },
            {
                std::string("Y este seria el segundo bloque a identificar\n")
            }
        };
        // clang-format on

        const std::vector<cmm::text_block> result =
            cmm::separate_blocks(source);

        CHECK(result == expected_result);
    }
    SECTION("Maneja multiples saltos de linea entre los bloques.") {
        const std::string source =
            "\n"
            "\n"
            "\n"
            "Hola\n"
            "\n"
            "\n"
            "\n"
            "\n"
            "Este tendria que ser un bloque\n"
            "para ser separado\n"
            "\n"
            "\n"
            "\n"
            "\n"
            "\n"
            "\n"
            "\n"
            "\n"
            "Y este seria el segundo bloque a identificar\n"
            "\n"
            "\n"
            "\n"
            "\n"
            "\n";

        // clang-format off
        const std::vector<cmm::text_block> expected_result = {
            {
                std::string("Hola\n")
            },
            {
                std::string("Este tendria que ser un bloque\n"),
                std::string("para ser separado\n")
            },
            {
                std::string("Y este seria el segundo bloque a identificar\n")
            }
        };
        // clang-format on

        const std::vector<cmm::text_block> result =
            cmm::separate_blocks(source);

        CHECK(result == expected_result);
    }
}
