#include "readfile.hpp"
#include <fstream>
#include <sstream>

namespace json {
    
    std::string fromFile(std::string path) {
        std::ifstream file = std::ifstream(path);
        std::stringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    }

}