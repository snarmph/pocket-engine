#include "pkfile.hpp"

namespace pk {
    bool file::open(const char *name, const char *mode) {
        handler = fopen(name, mode);
        if(!handler)
            return false;
        return true;
    }

    const char *file::read_whole() {
        long string_size;
        size_t read_size;
        pkassert(handler, "file not opened correctly");
        fseek(handler, 0, SEEK_END);
        string_size = ftell(handler);
        rewind(handler);

        char *buf = (char *) malloc(sizeof(char) * (string_size + 1));
        pkassert(buf, "couldn't allocate buffer");
        read_size = fread(buf, sizeof(char), string_size, handler);
        buf[read_size] = '\0';
        
        //pkassert(read_size == string_size, "read size and string size are different");
        return buf;
    }
} // namespace pk