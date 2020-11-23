#include <cstdio>
#include <cstdbool>

#include <glad/glad.h>
#include <SDL2/SDL.h>
#include <GL/gl.h>

#include "framework/engine.hpp"
#include "framework/window.hpp"
#include "framework/graphics.hpp"
#include "framework/sprite.hpp"
#include "framework/input.hpp"
#include "framework/shader.hpp"
#include "framework/mat.hpp"
#include "framework/matmath.hpp"

#include <cmath>

#define ZOOM_LEVEL 4

int main() {
    engine::init();
    window::create(
        "Pocket Engine", 
        {160 * ZOOM_LEVEL, 144 * ZOOM_LEVEL}
    );
    gfx::init();
    input::init();

    gfx::sprite_t spr1("assets/kris.png");
    spr1.set_atlas(10, 1);
    spr1.position = { 50.f, 50.f };

    gfx::sprite_t spr2("assets/kris.png");
    spr2.set_atlas(10, 1);
    spr2.position = { 0.f, 50.f };

    u32 start = engine::get_ticks();
    u32 update_after = 120;

    u32 frame1 = 0;
    u32 frame2 = 5;

    spr1.set_frame(frame1);
    spr2.set_frame(frame2);

    f32 a = 0;
    f32 b = 0;

    while(true) {
        engine::manage_events();
        glClear(GL_COLOR_BUFFER_BIT);

        gfx::basic_shader.use();
        gfx::basic_shader.set<mat3>("projection", gfx::projection);

        if(engine::get_ticks() - start > update_after) {
            frame1 = (frame1 == 9) ? 0 : frame1+1;
            frame2 = (frame2 == 9) ? 0 : frame2+1;
            spr1.set_frame(frame1);
            spr2.set_frame(frame2);
            start = engine::get_ticks();
        }

        a += 0.01f;
        b += 0.05f;
        spr2.position.x = (cos(a) * 50.f) + 60;
        spr2.position.y = (sin(b) * 50.f) + 60;

        spr1.render();
        spr2.render();

        window::swap_buffers();
    }

    // glDeleteVertexArrays(1, &vao);
    // glDeleteBuffers(1, &vbo);
    // glDeleteProgram(sh);
}