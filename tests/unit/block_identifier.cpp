#include<cmm/syntax_error.hpp>
#include <cmm/text_block.hpp>

#include "catch2/catch.hpp"

#include "block_examples.hpp"

// NOLINTNEXTLINE The complexity is due to the catch macros
TEST_CASE("cmm::identify_block_type", "[text_block]") {

    auto check_that_correctly_identifies =
        [](const char *raw_source, cmm::markdown_component_type expected) {
            const std::string                  source(raw_source);
            const std::vector<cmm::text_block> blocks =
                cmm::separate_blocks(source);

            for (const auto &b : blocks) {
                const auto type = cmm::identify_block_type(b);
                INFO(b) // No ;, seems like catch takes care of that
                CHECK(type == expected);
            }
        };

    auto check_syntax_errors =
        [](const char* raw_source) {
            const std::string                  source(raw_source);
            const std::vector<cmm::text_block> blocks =
                cmm::separate_blocks(source);

            for (const auto &b : blocks) {
                INFO(b) // No ;, seems like catch takes care of that
                CHECK_THROWS_AS(cmm::identify_block_type(b), cmm::syntax_error);
            }
        };

    SECTION("Atx Headings") {
        SECTION("Optimal cases") {
            check_that_correctly_identifies(
                raw_source_atx_headings,
                cmm::markdown_component_type::atx_headings);
        }
        SECTION("Syntax Errors") {
            const char *src = R"(
# The next line is just formed by spaces
                                        
# That should throw, because that
# might not be the intent of the user.
            )";
            check_syntax_errors(src);
        }
    }

    SECTION("Setext Headins") {
        SECTION("Optimal cases") {
            check_that_correctly_identifies(
                raw_source_setext_heading,
                cmm::markdown_component_type::setext_heading);
        }
    }

    SECTION("Indented code blocks") {
        SECTION("Optimal cases") {
            check_that_correctly_identifies(
                raw_source_indented_codeblock,
                cmm::markdown_component_type::indented_code_block);
        }
    }

    SECTION("Fenced code block openings") {
        SECTION("Optimal cases") {
            check_that_correctly_identifies(
                raw_source_fenced_code_block_opening,
                cmm::markdown_component_type::fenced_code_block_opening);
        }
    }

    SECTION("Fenced code block closings") {
        SECTION("Optimal cases") {
            check_that_correctly_identifies(
                raw_source_fenced_code_block_closing,
                cmm::markdown_component_type::fenced_code_block_closing);
        }
    }

    // Pending for future versions
    // SECTION("Html Block") {
    //     const std::string                  source();
    //     const std::vector<cmm::text_block> blocks =
    //         cmm::separate_blocks(source);

    //     for (const auto &b : blocks) {
    //         const auto type = cmm::identify_block_type(b);
    //         CHECK(type == cmm::markdown_component_type::undefined);
    //     }

    // }

    SECTION("Block quote") {
        SECTION("Optimal cases") {
            check_that_correctly_identifies(
                raw_source_block_quote,
                cmm::markdown_component_type::block_quote);
        }
    }

    SECTION("Ordered List") {
        SECTION("Optimal cases") {
            check_that_correctly_identifies(
                raw_source_ordered_list,
                cmm::markdown_component_type::ordered_list);
        }
    }

    SECTION("Unordered List") {
        SECTION("Optimal cases") {
            check_that_correctly_identifies(
                raw_source_unordered_list,
                cmm::markdown_component_type::unordered_list);
        }
        SECTION("Syntax Errors") {
            const char *src = R"(
* Check me first
                                        
         - There must be a problem in the above line
            )";
            check_syntax_errors(src);
        }
    }

    SECTION("Thematic Break") {
        SECTION("Optimal cases") {
            check_that_correctly_identifies(
                raw_source_thematic_break,
                cmm::markdown_component_type::thematic_break);
        }
    }

    SECTION("Paragraph") {
        SECTION("Optimal cases") {
            check_that_correctly_identifies(
                raw_source_paragraph,
                cmm::markdown_component_type::paragraph);
        }
    }
}
