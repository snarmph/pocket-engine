#include "sprite.hpp"
#include <pocket/math/mat.hpp>

namespace pk {
    void sprite::render(gfx::batcher &batch) {
        batch.push_matrix(mat3x2::from_position(position));
            batch.set_layer(gfx::layers::objects);
            batch.set_texture(texture);
            batch.rect(frame - offset, tex_coords);
        batch.pop_matrix();
    }
} // namespace pk