#include <pocket/pocket.hpp>

using pk::factory;
using pk::time;

#define ZOOM_LEVEL 2

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
        (f32)viewport.w, 0.f,
        0.f, (f32)viewport.h,
        -1.f,  1.f
    );

    pk::world &world = factory::get_world();
    gfx::batcher batch;

    vec2f camera_pos {-8.f, -16.f};

    //window::wireframe_on(true);
    
    //factory::new_tilemap("data/maps/pallet-town");
    factory::new_tilemap("data/maps/test.json");
    //auto player = factory::new_player("data/player/data.json");

    auto player_ctrl = world.get_first<pk::player_controller>();
    //vec2f &player_pos = player->get<pk::player_controller>()->position;

    u32 old = engine::get_ticks();
    gfx::basic_shader.use();
    gfx::basic_shader.set("projection", ortho);
    while(true) {
        u32 now = engine::get_ticks();
        u32 diff = now - old;
        old = now;
        time::dt = diff / 1000.f;
        time::fps = 1.f / time::dt;
        //printf("fps: %f         \r", time::fps);

        engine::manage_events();

        world.update();

        camera_pos = viewport.size() / 2;
        camera_pos -= player_ctrl->get_global_center();

        window::clear();
        batch.push_matrix(mat3x2::from_position(camera_pos));
            world.render(batch);
        batch.pop_matrix();
        
        batch.render();
        batch.clear();

        window::swap_buffers();
    }
}