#include <cmm/inlines.hpp>
#include <regex>

namespace cmm {

void process_strong_emphasis(std::string &source) {
    std::regex emphasis(R"(([^\\_*]*)[_*]{2}([^_*]*[^_*\\])[_*]{2})");
    std::string replacement("$1<strong>$2</strong>$3");

    std::string result = std::regex_replace(source, emphasis, replacement);

    source = std::move(result);
}

void process_emphasis(std::string &source) {
    std::regex emphasis(R"(([^\\_*]*)[_*]([^_*]*[^_*\\])[_*])");
    std::string replacement("$1<em>$2</em>$3");

    std::string result = std::regex_replace(source, emphasis, replacement);

    source = std::move(result);
}

void process_code_spans(std::string &source) {

}

void process_links(std::string &source) {

}

void process_images(std::string &source) {

}

} // namespace cmm
