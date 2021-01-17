#include <cstdio>

#ifdef _WIN32
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <pocket/engine.hpp>
#include <pocket/window.hpp>
#include <pocket/input/input.hpp>
#include <pocket/containers/vector.hpp>
#include <pocket/graphics/graphics.hpp>
#include <pocket/graphics/sprite.hpp>
#include <pocket/graphics/batch.hpp>
#include <pocket/math/mat.hpp>
#include <pocket/math/matmath.hpp>
#include <pocket/math/vec.hpp>
// #include <pocket/game/tilemap.hpp>
#include <pocket/components/player_controller.hpp>
#include <pocket/components/sprite.hpp>
#include <pocket/components/tilemap.hpp>

#define ZOOM_LEVEL 2

f32 dt = 0.f;

int main(int argc, char **args) {
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

    pk::world world;
    gfx::batcher batch;


    vec2f camera_pos {-8.f, -16.f};

    auto tilemap_ent = world.new_entity();
    auto tm = tilemap_ent->add<pk::tilemap>();
    tm->load("assets/map.json");

    //window::wireframe_on(true);

    u32 old = engine::get_ticks();

    auto player = world.new_entity();
    vec2f &player_pos = player->add<pk::sprite>()->position;
    player->add<pk::player_controller>();

    gfx::basic_shader.use();
    gfx::basic_shader.set("projection", ortho);
    f32 angle = 0;
    while(true) {
        u32 now = engine::get_ticks();
        u32 diff = now - old;
        old = now;
        dt = diff / 1000.f;


        engine::manage_events();

        world.update();

        camera_pos = viewport.size() / 2;
        camera_pos -= player_pos;

        window::clear();

        batch.push_matrix(mat3x2::from_position(camera_pos));
            // tm.render(batch);
            
            // batch.set_layer(gfx::layers::objects);
            world.render(batch);
        batch.pop_matrix();

        batch.render();
        batch.clear();

        window::swap_buffers();
    }
}

// #include "pocket/world.hpp"

// namespace pk {
//     struct animator : public component {
//         void awake() override {
//             //printf("awakening animator\n");
//         }

//         void update() override {
//             printf(" >>> updating animator <<< \n");
//         }
//     };
// } // namespace pk 

// int main() {
//     pk::world w;
//     auto e = w.new_entity();
//     e->add<pk::animator>();

//     w.update();
// }