#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "types.hpp"
#include "vec.hpp"

namespace gfx {
    struct texture_t {
        u32 id;
        vec2i size;

        texture_t();
        texture_t(const char *fname);

        void load(const char *fname);

        void bind();
        void unbind();
    };
} // namespace gfx

#endif