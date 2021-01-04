#include <cmm/inlines.hpp>
#include <regex>

namespace cmm {

void process_inlines(std::string &source) {

}

void process_code_spans(std::string &source) {

}

void process_emphasis(std::string &source) {
    std::regex emphasis(R"([_*]([^_*]+)[_*])");
    std::string replacement("<em>$1</em>");

    std::string result = std::regex_replace(source, emphasis, replacement);

    source = std::move(result);
}

void process_strong_emphasis(std::string &source) {
    std::regex emphasis(R"([_*][_*]([^_*]+)[_*][_*])");
    std::string replacement("<strong>$1</strong>");

    std::string result = std::regex_replace(source, emphasis, replacement);

    source = std::move(result);
}

void process_links(std::string &source) {

}

void process_images(std::string &source) {

}

} // namespace cmm
