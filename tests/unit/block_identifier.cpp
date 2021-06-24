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
            INFO(b);
            CHECK(type == cmm::markdown_component_type::atx_headings);
        }
    }

    SECTION("Setext Headins") {
        const std::string                  source(raw_source_setext_heading);
        const std::vector<cmm::text_block> blocks =
            cmm::separate_blocks(source);

        for (const auto &b : blocks) {
            const auto type = cmm::identify_block_type(b);
            CHECK(type == cmm::markdown_component_type::setext_heading);
        }
    }

    SECTION("Indented code blocks") {
        const std::string                  source(raw_source_indented_codeblock);
        const std::vector<cmm::text_block> blocks =
            cmm::separate_blocks(source);

        for (const auto &b : blocks) {
            const auto type = cmm::identify_block_type(b);
            CHECK(type == cmm::markdown_component_type::indented_code_block);
        }
    }

    SECTION("Fenced code block openings") {
        const std::string                  source(raw_source_fenced_code_block_opening);
        const std::vector<cmm::text_block> blocks =
            cmm::separate_blocks(source);

        for (const auto &b : blocks) {
            const auto type = cmm::identify_block_type(b);
            CHECK(type == cmm::markdown_component_type::fenced_code_block_opening);
        }
    }

    SECTION("Fenced code block closings") {
        const std::string                  source(raw_source_fenced_code_block_closing);
        const std::vector<cmm::text_block> blocks =
            cmm::separate_blocks(source);

        for (const auto &b : blocks) {
            const auto type = cmm::identify_block_type(b);
            CHECK(type == cmm::markdown_component_type::fenced_code_block_closing);
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
        const std::string                  source(raw_source_block_quote);
        const std::vector<cmm::text_block> blocks =
            cmm::separate_blocks(source);

        for (const auto &b : blocks) {
            const auto type = cmm::identify_block_type(b);
            CHECK(type == cmm::markdown_component_type::block_quote);
        }

    }

    SECTION("Ordered List") {
        const std::string                  source(raw_source_ordered_list);
        const std::vector<cmm::text_block> blocks =
            cmm::separate_blocks(source);

        for (const auto &b : blocks) {
            const auto type = cmm::identify_block_type(b);
            CHECK(type == cmm::markdown_component_type::ordered_list);
        }

    }

    SECTION("Unordered List") {
        const std::string                  source(raw_source_unordered_list);
        const std::vector<cmm::text_block> blocks =
            cmm::separate_blocks(source);

        for (const auto &b : blocks) {
            const auto type = cmm::identify_block_type(b);
            CHECK(type == cmm::markdown_component_type::unordered_list);
        }

    }

    SECTION("Thematic Break") {
        const std::string                  source(raw_source_thematic_break);
        const std::vector<cmm::text_block> blocks =
            cmm::separate_blocks(source);

        for (const auto &b : blocks) {
            const auto type = cmm::identify_block_type(b);
            CHECK(type == cmm::markdown_component_type::thematic_break);
        }

    }

    SECTION("Paragraph") {
        const std::string                  source(raw_source_paragraph);
        const std::vector<cmm::text_block> blocks =
            cmm::separate_blocks(source);

        for (const auto &b : blocks) {
            const auto type = cmm::identify_block_type(b);
            CHECK(type == cmm::markdown_component_type::paragraph);
        }

    }
}
