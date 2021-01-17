#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <pocket/math/vec.hpp>
#include <pocket/graphics/gfx_api.h>

namespace window {
    extern const char *name;
    extern vec2i size;

    void create(const char *name, const vec2i &size);
    void destroy();

    void vsync_on(bool on);
    void wireframe_on(bool on);

    void clear();
    void swap_buffers();
} // namespace window

#endif