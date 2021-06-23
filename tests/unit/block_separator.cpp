#include <cmm/text_block.hpp>

#include "catch2/catch.hpp"

// The cognitive complexity is due to the expansion of the catch2
// macros
//
// So: NOLINTNEXTLINE
TEST_CASE("cmm::separate_blocks", "[text_block]") {
    SECTION("Resuelve el caso optimo") {
        const std::string source =
            "Hola\n"
            "\n"
            "Este tendria que ser un bloque\n"
            "para ser separado\n"
            "\n"
            "Y este seria el segundo bloque a identificar\n";

        const std::vector<cmm::text_block> expected_result = {
            std::string("Hola\n"),
            std::string("Este tendria que ser un bloque\npara ser separado\n"),
            std::string("Y este seria el segundo bloque a identificar\n")};

        const std::vector<cmm::text_block> result =
            cmm::separate_blocks(source);

        CHECK(result == expected_result);
    }

    SECTION("Retorna un std::vector vacio si no hay texto") {
        const std::string source{};
        const std::vector<cmm::text_block> expected_result;

        const std::vector<cmm::text_block> result =
            cmm::separate_blocks(source);

        CHECK(result == expected_result);
    }

    SECTION("Maneja un unico bloque") {
        const std::string source = "Hola\n";
        const std::vector<cmm::text_block> expected_result = {
            std::string("Hola\n")
        };

        const std::vector<cmm::text_block> result =
            cmm::separate_blocks(source);

        CHECK(result == expected_result);
    }

    SECTION("Maneja la falta de un salto de linea al final") {
        const std::string source =
            "Hola\n"
            "\n"
            "Este tendria que ser un bloque\n"
            "para ser separado\n"
            "\n"
            "Y este seria el segundo bloque a identificar";

        const std::vector<cmm::text_block> expected_result = {
            std::string("Hola\n"),
            std::string("Este tendria que ser un bloque\npara ser separado\n"),
            std::string("Y este seria el segundo bloque a identificar\n")};

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

        const std::vector<cmm::text_block> expected_result = {
            std::string("Hola\n"),
            std::string("Este tendria que ser un bloque\npara ser separado\n"),
            std::string("Y este seria el segundo bloque a identificar\n")};

        const std::vector<cmm::text_block> result =
            cmm::separate_blocks(source);

        CHECK(result == expected_result);
    }
}
