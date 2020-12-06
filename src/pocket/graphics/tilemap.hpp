#ifndef TILEMAP_HPP
#define TILEMAP_HPP

#include <array>

#include <pocket/containers/vector.hpp>
#include <pocket/math/rect.hpp>
#include "texture.hpp"

namespace gfx {
    struct tilemap_layer {
        f32 z_pos = -0.5f;
        mem::vector<rectf> frames;
        mem::vector<rectf> texcoords;
    };

    struct tilemap {
        texture_t texture;
        std::array<tilemap_layer, 3> layers;
        f32 tile_size = 32.f;
        u32 width = 0;
        u32 height = 0;

        tilemap() = default;
        tilemap(const char *fname);

        void load(const char *fname);
    };

} // namespace gfx


#endif