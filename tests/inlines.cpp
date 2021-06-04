#include <array>
#include <cmm/cmm.hpp>

#include "catch2/catch.hpp"


TEST_CASE("Code Spans", "[code_span] [inline]") {
    constexpr size_t                           number_of_entries = 3;
    std::array<std::string, number_of_entries> entries{
        "`Hola`",
        "``Hola amigo``",
        "````Hola ` como `` estas?````\\"};

    std::array<std::string, number_of_entries> results{
        "<code>Hola</code>",
        "<code>Hola amigo</code>",
        "<code>Hola ` como `` estas?</code>\\"};

    for (size_t i = 0; i < number_of_entries; i++) {
        std::string res = cmm::process_inlines(entries[i]); // NOLINT
        CHECK(res == results[i]);                           // NOLINT
    }
}

TEST_CASE("Emphasis", "[emphasis] [inline]") {
    constexpr size_t                           number_of_entries = 7;
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
        auto res = cmm::process_inlines(entries[i]); // NOLINT
        CHECK(res == results[i]);                    // NOLINT
    }
}

TEST_CASE("Links", "[link] [inline]") {
    constexpr size_t                           number_of_entries = 8;
    std::array<std::string, number_of_entries> entries = {
        "[]()",
        "[text_all_together]()",
        "[text_all_together](/url)",
        "[text with spaces](/url)",
        // clang-format off
        "[text with spaces](/and/a/non/realisticly/long/url//how/are/you//im/fine//this/is/getting/kind/of/boring/to/write//i/imagine/it/will/be/hard/to/read)",
        // clang-format on
        "[text with spaces](/url single_word_title)",
        "[text with spaces](/url Multi word title)",
        "[Did you *know* we **allow** other `inlines` iside here?](/url Multi word title)",
    };

    std::array<std::string, number_of_entries> results = {
        R"(<a href="" title=""></a>)",
        R"(<a href="" title="">text_all_together</a>)",
        R"(<a href="/url" title="">text_all_together</a>)",
        R"(<a href="/url" title="">text with spaces</a>)",
        R"(<a href="/and/a/non/realisticly/long/url//how/are/you//im/fine//this/is/getting/kind/of/boring/to/write//i/imagine/it/will/be/hard/to/read" title="">text with spaces</a>)",
        R"(<a href="/url" title="single_word_title">text with spaces</a>)",
        R"(<a href="/url" title="Multi word title">text with spaces</a>)",
        R"(<a href="/url" title="Multi word title">Did you <em>know</em> we <strong>allow</strong> other <code>inlines</code> iside here?</a>)",

    };

    for (size_t i = 0; i < entries.size(); i++) {
        auto res = cmm::process_inlines(entries[i]); // NOLINT
        CHECK(res == results[i]);                    // NOLINT
    }
}
