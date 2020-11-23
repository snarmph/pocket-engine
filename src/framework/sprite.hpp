#ifndef SPRITE_HPP
#define SPRITE_HPP

#include "texture.hpp"
#include "shader.hpp"
#include "vec.hpp"

namespace gfx {
    struct sprite_t {
        vec2f     position;
        vec2f     size;
        shader_t  shader;
        texture_t texture;
        u32       vao;
        u32       texture_vbo;
        u32       index_vbo;

        u32 columns;
        u32 rows;

        sprite_t();
        sprite_t(const char *texture_path);
        sprite_t(texture_t &txt);

        void set_atlas(u32 c, u32 r);
        void set_frame(u32 n);
        // void set_texcoords(f32 x, f32 y, f32 w, f32 h);

        void init();

        void render();
    };
} // namespace gfx

#endif