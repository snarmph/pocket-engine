#pragma once
#include <pocket/core/world.hpp>
#include <pocket/graphics/texture.hpp>
#include <pocket/math/rect.hpp>

namespace pk {
    struct sprite : public component {
        void render(gfx::batcher &batch) override;

        gfx::texture_t texture;
        rectf tex_coords;
        rectf frame;
        vec2f offset_center;
    };
} // namespace pk 