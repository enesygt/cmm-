#include <array>
#include <cmm/cmm.hpp>

#include "catch2/catch.hpp"

constexpr size_t number_of_entries = 9;

TEST_CASE("Emphasis", "[emphasis] [inline]") {
    std::array<std::string, number_of_entries> entries = {
        "*Hola*",
        "**Hola**",
        "**",
        "****",
        "Hola amigo *como* *estas*?",
        "Hola amigo **como** **estas**?",
        "Hola *amigo* como **estas?**",
        "Hola **amigo** como *estas?*",
        "***Hola***"
    };

    std::array<std::string, number_of_entries> results = {
        "<em>Hola</em>",
        "<strong>Hola</strong>",
        "**",
        "****",
        "Hola amigo <em>como</em> <em>estas</em>?",
        "Hola amigo <strong>como</strong> <strong>estas</strong>?",
        "Hola <em>amigo</em> como <strong>estas?</strong>",
        "Hola <strong>amigo</strong> como <em>estas?</em>",
        "<em><strong>Hola</strong></em>"
    };

    for (size_t i = 0; i < entries.size(); i++) {
        auto res = cmm::parce(entries[i]);
        CHECK(res == results[i]);
    }
}
