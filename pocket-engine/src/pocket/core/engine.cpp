#include "engine.hpp"

#include <cstdio>
#include <sokol/sokol.h>

#include <pocket/pocket.hpp>

#include <pocket/scripts/script_manager.hpp>

namespace {
    u64 time_old = 0;
    recti viewport;
} // namespace 

namespace engine {
    void init();
    void frame();
    void cleanup();
    void handle_event(const sapp_event *e);

    void init(options &opts) {
        sapp_desc options{};

        options.width = opts.resolution.x * opts.zoom;
        options.height = opts.resolution.y * opts.zoom;
        options.window_title = opts.name.cstr();
        options.fullscreen = opts.fullscreen;

        options.init_cb = init;
        options.frame_cb = frame;
        options.cleanup_cb = cleanup;
        options.event_cb = handle_event;
        options.fail_cb = [](const char *msg) {
            printf("[ERROR] %s\n", msg);
        };

        viewport = recti(0, 0, opts.resolution.x, opts.resolution.y);

        sapp_run(options);
    }

    //=============================================

    using pk::factory;

    gfx::batcher batch;
    pk::world &world = factory::get_world();

    pk::script_manager scripts;

    vec2f camera_pos;
    pk::player_controller *player_ctrl = nullptr;

    void init() {
        printf("initializing\n");

        // sokol time init
        stm_setup();
        time_old = stm_now();

        // sokol gfx init
        sg_desc gfx_opts{};
        gfx_opts.context = sapp_sgcontext();
        sg_setup(gfx_opts);

        sgl_desc_t gl_opts{};
        gl_opts.sample_count = sapp_sample_count();
        sgl_setup(gl_opts);

        // everything else

        input::init();
        batch.init();

        math::orthographic(
            batch.uniform_mat,
            160.f, 0.f,
            0.f, 144.f,
            -1.f, 1.f
        );

        factory::new_tilemap("data/maps/test.json");
        factory::new_tilemap("data/maps/other.json");

        player_ctrl = world.get_first<pk::player_controller>();
        pkassert(player_ctrl, "player ctrl is nullptr");
    }

    void frame() {
        time::dt = stm_sec(stm_laptime(&time_old));
        time::fps = 1.f / time::dt;
        
        // == UPDATE =================================

        world.update();

        scripts.update();

        camera_pos = viewport.size() / 2;
        camera_pos -= player_ctrl->get_global_center();

        // == RENDER =================================

        batch.push_matrix(mat3x2::from_position(camera_pos));
            world.render(batch);
        batch.pop_matrix();

        batch.render();
        batch.clear();
    }

    void handle_event(const sapp_event *e) {
        switch (e->type){
        case SAPP_EVENTTYPE_KEY_DOWN:
            input::set_key_down(e->key_code);
            break;
        case SAPP_EVENTTYPE_KEY_UP:
            input::set_key_up(e->key_code);
            break;
        case SAPP_EVENTTYPE_QUIT_REQUESTED:
            printf("application wants to quit\n");
            break;
        default:
            break;
        }

        if (input::is_key_down(SAPP_KEYCODE_ESCAPE))
            sapp_request_quit();
    }

    void cleanup() {
        printf("cleaning up\n");
        sg_shutdown();
    }
    
    //=============================================

    u64 get_ticks() {
        return stm_now();
    }
} // namespace engine