#include <cstdio>

#include <pocket/engine.hpp>
#include <pocket/window.hpp>
#include <pocket/input/input.hpp>
#include <pocket/graphics/graphics.hpp>
#include <pocket/graphics/sprite.hpp>
#include <pocket/graphics/batch.hpp>
#include <pocket/graphics/tilemap.hpp>
#include <pocket/math/mat.hpp>
#include <pocket/math/matmath.hpp>
#include <pocket/containers/vector.hpp>

#define ZOOM_LEVEL 5

int main() {
    recti viewport {0, 0, 160, 144};

    engine::init();
    window::create(
        "Pocket Engine",
        viewport.size() * ZOOM_LEVEL
    );
    gfx::init();
    input::init();
    window::vsync_on(true);

    mat4 ortho;
    math::orthographic(
        ortho,
        viewport.w, 0.f,
        0.f,    viewport.h,
        -1.f,  1.f
    );

    gfx::sprite spr;
    spr.texture.load("assets/kris.png");
    spr.frame = {88.0f, 0.0f, 16.f, 16.f};
    spr.tex_coords = {0.f, 0.f, 0.1f, 1.f};

    gfx::tilemap tm;
    tm.load("assets/map.json");

    gfx::batcher batch;

//    window::wireframe_on(true);

    gfx::basic_shader.use();
    gfx::basic_shader.set("projection", ortho);
    f32 angle = 0;
    while(true) {
        engine::manage_events();
        window::clear();

        batch.set_texture(tm.texture);
        for(size_t i=0; i<1; i++)
            for(size_t j=0; j<tm.layers[i].frames.size(); j++)
                batch.rect(tm.layers[i].frames[j], tm.layers[i].texcoords[j]);

        batch.set_texture(spr.texture);
        batch.rect(spr.frame, spr.tex_coords);

        batch.set_texture(tm.texture);
        for(size_t i=1; i<tm.layers.size(); i++)
            for(size_t j=0; j<tm.layers[i].frames.size(); j++)
                batch.rect(tm.layers[i].frames[j], tm.layers[i].texcoords[j]);

        spr.frame.x = viewport.center().x;
        spr.frame.y = viewport.center().y;

        spr.frame.x += sinf(angle) * 20.f;

        angle += 0.1f;

        batch.render();
        batch.clear();

        window::swap_buffers();
    }
}