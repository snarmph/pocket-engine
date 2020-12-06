#ifndef PKFILE_HPP
#define PKFILE_HPP

#include <cstdio>
#include <cstdlib>

#include <pocket/types.hpp>
#include <pocket/util/pkassert.h>

namespace pk {
    struct file {
        // byte *buffer;
        FILE *handler;
        // size_t oldbuffersize;

        file() {
            // buffer = nullptr;
            handler = nullptr;
            // oldbuffersize = 0;
        }

        ~file() {
            if(handler)
                fclose(handler);
            // if(buffer)
            //     free(buffer);
        }

        bool open(const char *name, const char *mode = "r");

        const byte *read_whole();
    };

} // namespace pk

#endif