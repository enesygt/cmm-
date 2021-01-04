#ifndef CMM_INLINES_HPP
#define CMM_INLINES_HPP

#include <string>

namespace cmm {

void process_inlines(std::string &source);
void process_code_spans(std::string &source);
void process_emphasis(std::string &source);
void process_strong_emphasis(std::string &source);
void process_links(std::string &source);
void process_images(std::string &source);

} // namespace cmm

#endif
