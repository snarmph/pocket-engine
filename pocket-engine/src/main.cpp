//#include <pocket/pocket.hpp>
//
//using pk::factory;
//using pk::time;
//
//constexpr int zoom_level = 2;
//
//int main(int argc, char **args) {
//    const recti viewport {0, 0, 160, 144};
//
//    engine::init();
//    window::create(
//        "Pocket Engine",
//        viewport.size() * zoom_level
//    );
//    gfx::init();
//    input::init();
//    window::vsync_on(true);
//
//    mat4 ortho;
//    math::orthographic(
//        ortho,
//        (f32)viewport.w, 0.f,
//        0.f, (f32)viewport.h,
//        -1.f,  1.f
//    );
//
//    pk::world &world = factory::get_world();
//    gfx::batcher batch;
//
//    vec2f camera_pos {-8.f, -16.f};
//
//    window::vsync_on(true);
//    //window::wireframe_on(true);
//    
//    factory::new_tilemap("data/maps/test.json");
//    factory::new_tilemap("data/maps/other.json");
//    //auto player = factory::new_player("data/player/data.json");
//
//    auto player_ctrl = world.get_first<pk::player_controller>();
//
//    u32 old = engine::get_ticks();
//    gfx::basic_shader.use();
//    gfx::basic_shader.set("projection", ortho);
//    
//    while(true) {
//        u32 now = engine::get_ticks();
//        u32 diff = now - old;
//        old = now;
//        time::dt = diff / 1000.f;
//        time::fps = 1.f / time::dt;
//        //printf("dt: %u         \r", diff);
//
//        engine::manage_events();
//
//        world.update();
//
//        camera_pos = viewport.size() / 2;
//        camera_pos -= player_ctrl->get_global_center();
//
//        window::clear();
//        batch.push_matrix(mat3x2::from_position(camera_pos));
//            world.render(batch);
//        batch.pop_matrix();
//        
//        batch.render();
//        batch.clear();
//        
//        window::swap_buffers();
//    }
//}

#include <pocket/pocket.hpp>

int main() {

	engine::options opts;

	opts.name = "pocket engine";
	opts.resolution = { 160, 144 };
	opts.zoom = 2,

	engine::init(opts);
}