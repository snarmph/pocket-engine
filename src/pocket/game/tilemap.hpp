#ifndef TILEMAP_HPP
#define TILEMAP_HPP

#include <array>

#include <pocket/containers/vector.hpp>
#include <pocket/math/rect.hpp>
#include <pocket/graphics/texture.hpp>
#include <pocket/graphics/batch.hpp>

#include "entity.hpp"

namespace game {
    struct tilemap_layer {
        mem::vector<rectf> frames;
        mem::vector<rectf> texcoords;
    };

    struct tilemap {
        gfx::texture_t texture;
        std::array<tilemap_layer, 3> layers;
        f32 tile_size = 32.f;
        u32 width = 0;
        u32 height = 0;

        tilemap() = default;
        tilemap(const char *fname);

        void render(gfx::batcher &b);

        void load(const char *fname);
    };

} // namespace gfx


#endif