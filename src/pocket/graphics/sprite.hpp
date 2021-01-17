#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <pocket/graphics/texture.hpp>
#include <pocket/graphics/shader.hpp>
#include <pocket/math/rect.hpp>

namespace gfx {
    struct sprite {
        texture_t texture;
        rectf tex_coords;
        rectf frame;
        vec2f offset_center;
    };
} // namespace gfx

#endif