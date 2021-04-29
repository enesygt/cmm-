#include <array>
#include <cmm/cmm.hpp>

#include "catch2/catch.hpp"


TEST_CASE("Code Spans", "[code_span] [inline]") {
    constexpr size_t number_of_entries = 3;
    std::array<std::string, number_of_entries> entries {
        "`Hola`",
        "``Hola amigo``",
        "````Hola ` como `` estas?````\\"
    };

    std::array<std::string, number_of_entries> results {
        "<code>Hola</code>",
        "<code>Hola amigo</code>",
        "<code>Hola ` como `` estas?</code>\\"
    };

    for (size_t i = 0; i < number_of_entries; i++) {
        std::string res = cmm::process_inlines(entries[i]);
        CHECK(res == results[i]);
    }
}

TEST_CASE("Emphasis", "[emphasis] [inline]") {
    constexpr size_t number_of_entries = 7;
    std::array<std::string, number_of_entries> entries = {
        "*Hola*",
        "**Hola**",
        "***Hola***",
        "**Hola, como *estas?***",
        "*",
        "**",
        "*Hola, **como** estas?*",
    };

    std::array<std::string, number_of_entries> results = {
        "<em>Hola</em>",
        "<strong>Hola</strong>",
        "<strong><em>Hola</em></strong>",
        "<strong>Hola, como <em>estas?</em></strong>",
        "<em>",
        "<strong>",
        "<em>Hola, <strong>como</strong> estas?</em>",
    };

    for (size_t i = 0; i < entries.size(); i++) {
        auto res = cmm::process_inlines(entries[i]);//NOLINT
        CHECK(res == results[i]);//NOLINT
    }
}
