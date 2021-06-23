#include <cmm/text_block.hpp>

#include <sstream>
#include <string>

using cmm::text_block;

std::vector<text_block> cmm::separate_blocks(const std::string& source) {
    std::vector<text_block> result;
    std::stringstream src(source);
    std::stringstream buffer;

    text_block temp;

    while (src) {
        // Clean up any leading \n
        while (src && src.peek() == '\n') {
            src.get();
        }

        // Read until you find a line with only one \n
        while (std::getline(src, temp)) {

            // If got to a \n push the result and clean the buffer.
            if (temp.empty()) {
                result.push_back(buffer.str());
                buffer.str("");
                break;
            }

            buffer << temp << '\n';
        }
    }

    // If the document ends in a single \n or none, then the last block was not
    // saved
    temp = buffer.str();
    if (!temp.empty()) {
        result.push_back(std::move(temp));
    }

    return result;
}
