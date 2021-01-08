#ifndef CMM_INLINES_HPP
#define CMM_INLINES_HPP

#include <cmm/config.hpp>
#include <string>

namespace cmm {

void process_strong_emphasis(std::string &source);
void process_emphasis(std::string &source);
void process_code_spans(std::string &source);
void process_links(std::string &source);
void process_images(std::string &source);

void inline process_inlines(std::string &source) {
    process_strong_emphasis(source);
    process_emphasis(source);
}


} // namespace cmm

#endif
