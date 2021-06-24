#include <cmm/text_block.hpp>

#include "catch2/catch.hpp"

#include "block_examples.hpp"

// NOLINTNEXTLINE The complexity is due to the catch macros
TEST_CASE("cmm::identify_block_type", "[text_block]") {

    /*     SECTION ("Template") {
     *         const std::string source(raw_source_type);
     *         const std::vector<cmm::text_block> blocks =
     *             cmm::separate_blocks(source);
     *
     *         for (const auto& b : blocks) {
     *             const auto type = cmm::identify_block_type(b);
     *             CHECK(type == cmm::markdown_component_type::undefined);
     *         }
     *      }
     *
     */

    SECTION("Atx Headings") {

        const std::string                  source(raw_source_atx_headings);
        const std::vector<cmm::text_block> blocks =
            cmm::separate_blocks(source);

        for (const auto &b : blocks) {
            const auto type = cmm::identify_block_type(b);
            CHECK(type == cmm::markdown_component_type::atx_headings);
        }
    }

    SECTION("Setext Headins") {

        const std::string                  source(raw_source_setext_heading);
        const std::vector<cmm::text_block> blocks =
            cmm::separate_blocks(source);

        for (const auto &b : blocks) {
            const auto type = cmm::identify_block_type(b);
            CHECK(type == cmm::markdown_component_type::atx_headings);
        }
    }

    SECTION("Indented code blocks") {}
    SECTION("Fenced code block") {}
    SECTION("Html Block") {}
    SECTION("Block quote") {}
    SECTION("List") {}
    SECTION("Thematic Break") {}
    SECTION("Paragraph") {}
}
