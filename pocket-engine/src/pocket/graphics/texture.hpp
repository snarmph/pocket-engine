#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <sokol/sokol.h>

#include <pocket/core/types.hpp>
#include <pocket/math/vec.hpp>

namespace gfx {
    struct texture_t {
        sg_image image_id{};
        vec2i size;

        texture_t() = default;
        texture_t(const char *fname);

        void load(const char *fname);
        void load_from_memory(byte *data);
    };
} // namespace gfx

#endif