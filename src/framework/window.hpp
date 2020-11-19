#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "vec.hpp"

namespace window {
    extern const char *name;
    // extern vec2i position;
    extern vec2i size;

    void create(const char *name, const vec2i &size);
    void destroy();
} // namespace window

#endif