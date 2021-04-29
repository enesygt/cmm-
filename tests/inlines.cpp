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

/* 
TEST_CASE("Emphasis", "[emphasis] [inline]") {
    constexpr size_t number_of_entries = 32;
    std::array<std::string, number_of_entries> entries = {
        "*Hola*",
        "**Hola**",
        "**",
        "****",
        "Hola amigo *como* *estas*?",
        "Hola amigo **como** **estas**?",
        "Hola *amigo* como **estas?**",
        "Hola **amigo** como *estas?*",
        "***Hola***",
        "_Hola_",
        "__Hola__",
        "__",
        "____",
        "Hola amigo _como_ _estas_?",
        "Hola amigo __como__ __estas__?",
        "Hola _amigo_ como __estas?__",
        "Hola __amigo__ como _estas?_",
        "___Hola___",
        R"(\*Hola\*)",
        R"(\*\*Hola\*\*)",
        R"(Hola amigo \*como\* \*estas\*?)",
        R"(Hola amigo \*\*como\*\* \*\*estas\*\*?)",
        R"(Hola \*amigo\* como \*\*estas?\*\*)",
        R"(Hola \*\*amigo\*\* como \*estas?\*)",
        R"(\*\*\*Hola\*\*\*)",
        R"(\_Hola\_)",
        R"(\_\_Hola\_\_)",
        R"(Hola amigo \_como\_ \_estas\_?)",
        R"(Hola amigo \_\_como\_\_ \_\_estas\_\_?)",
        R"(Hola \_amigo\_ como \_\_estas?\_\_)",
        R"(Hola \_\_amigo\_\_ como \_estas?\_)",
        R"(\_\_\_Hola\_\_\_)"
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
        "<em><strong>Hola</strong></em>",
        "<em>Hola</em>",
        "<strong>Hola</strong>",
        "__",
        "____",
        "Hola amigo <em>como</em> <em>estas</em>?",
        "Hola amigo <strong>como</strong> <strong>estas</strong>?",
        "Hola <em>amigo</em> como <strong>estas?</strong>",
        "Hola <strong>amigo</strong> como <em>estas?</em>",
        "<em><strong>Hola</strong></em>",
        R"(*Hola*)",
        R"(**Hola**)",
        R"(Hola amigo *como* *estas*?)",
        R"(Hola amigo **como** **estas**?)",
        R"(Hola *amigo* como **estas?**)",
        R"(Hola **amigo** como *estas?*)",
        R"(***Hola***)",
        R"(_Hola_)",
        R"(__Hola__)",
        R"(Hola amigo _como_ _estas_?)",
        R"(Hola amigo __como__ __estas__?)",
        R"(Hola _amigo_ como __estas?__)",
        R"(Hola __amigo__ como _estas?_)",
        R"(___Hola___)"
    };

    for (size_t i = 0; i < entries.size(); i++) {
        auto res = cmm::process_inlines(entries[i]);//NOLINT
        CHECK(res == results[i]);//NOLINT
    }
}
*/
