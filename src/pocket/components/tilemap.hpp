#pragma once

#include <pocket/world.hpp>
#include <pocket/math/rect.hpp>
#include <pocket/graphics/texture.hpp>

namespace pk {

    struct tilemap : public component {
        virtual void render(gfx::batcher &batch);

        void load(const char *fname);

        struct layer {
            mem::vector<rectf> frames;
            mem::vector<rectf> texcoords;
        };

        gfx::texture_t texture;
        std::array<layer, 3> layers;
        f32 tile_size = 16.f;
        u32 width = 0;
        u32 height = 0;
    };
    
} // namespace pk 