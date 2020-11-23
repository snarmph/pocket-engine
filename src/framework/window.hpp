#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "vec.hpp"

#include <SDL2/SDL.h>

namespace window {
    extern const char *name;
    extern vec2i size;

    void create(const char *name, const vec2i &size);
    void destroy();

    void swap_buffers();
} // namespace window

#endif