#include "sprite.hpp"

#include <glad/glad.h>
#include <SDL2/SDL.h>
#include <GL/gl.h>

#include "graphics.hpp"
#include "pkassert.h"

namespace {
    f32 tex_coords[] = {
        0.f, 0.f, 
        1.f, 0.f, 
        1.f, 1.f, 
        0.f, 1.f
    };

    f32 vertices[] = {
        0.f, 0.f,
        1.f, 0.f,
        1.f, 1.f,
        0.f, 1.f
    };

    u32 ebos[] = {
        0, 1, 2, 
        2, 3, 0
    };
} // namespace

namespace gfx {
    sprite_t::sprite_t() {
        init();
    }

    sprite_t::sprite_t(const char *texture_path) {
        texture.load(texture_path);
        init();
    }

    sprite_t::sprite_t(texture_t &txt) {
        texture = txt;
        init();
    }

    void sprite_t::set_atlas(u32 c, u32 r) {
        columns = c;
        rows = r;
        size.x = texture.size.x / c;
        size.y = texture.size.y / r;
    }

    void sprite_t::set_frame(u32 n) {
        pkassert(n < rows * columns, "frame is more than maximum possible");
        f32 x = (n % columns) * (float)(size.x / texture.size.x);
        f32 y = (n / columns) * (float)(size.y / texture.size.y);

        f32 w = x + 1.f / columns;
        f32 h = y + 1.f / rows;

        f32 new_tc[] = {
            x, y,
            w, y,
            w, h,
            x, h
        };

        glBindBuffer(GL_ARRAY_BUFFER, texture_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(new_tc), new_tc, GL_DYNAMIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void sprite_t::init() {
        u32 ebo;
        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &index_vbo);
        glGenBuffers(1, &texture_vbo);
        glGenBuffers(1, &ebo);

        glBindVertexArray(vao);

        glBindBuffer(GL_ARRAY_BUFFER, index_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);
        // position attribute
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void *)0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, texture_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(tex_coords), tex_coords, GL_DYNAMIC_DRAW);
        // // textureCoord attribute
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*) 0);
        glEnableVertexAttribArray(1);
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(ebos), &ebos, GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0); 
    }

    void sprite_t::render() {
        gfx::basic_shader.set<vec2f>("scale", size);
        gfx::basic_shader.set<vec2f>("position", position);

        texture.bind();

        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        texture.unbind();
    }
} // namespace gfx