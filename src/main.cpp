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
#include <pocket/math/vec.hpp>

//#include <pocket/ecs/ecs.hpp>
#include <pocket/ecs/other.hpp>

#define ZOOM_LEVEL 5

//ecs::coordinator coord;

struct gravity {
    vec2f force;
};

struct rigidbody {
    vec2f velocity;
    vec2f acceleration;
};

struct transform {
    vec2f position;
    vec2f rotation;
    vec2f scale;
};

struct player {
    player(ecs::scene &scene) {
        id = scene.new_entity();
        auto t = scene.assign<transform>(id);
    }

    ecs::entity id;
};

/*
 * ecs::entity player = scene.new();
 *
 * */

//struct physics_system : public ecs::system {
//    void update() {
//        for(const auto &e: entities) {
//            /*
//             * e.get<rigidbody>();
//             * */
//            auto &rigidbd      = coord.get_component<rigidbody>(e);
//            auto &grav         = coord.get_component<gravity>(e);
//            const auto &transf = coord.get_component<transform>(e);
//
////            transf.position = rigidbd.velocity;
//            printf("grav: %f %f\n", grav.force.x, grav.force.y);
//        }
//    }
//};

int ecs::component_counter = 0;

int main() {
    ecs::scene scene;
    ecs::entity e1 = scene.new_entity();
    ecs::entity e2 = scene.new_entity();
    ecs::entity e3 = scene.new_entity();
    auto ptr1 = scene.assign<transform>(e1);
    ptr1->scale = {2.f, 3.f};
    scene.assign<rigidbody>(e1);
    scene.assign<gravity>(e1);
    auto ptr2 = scene.assign<transform>(e2);
    ptr2->scale = {153.f, 4573.f};
    scene.assign<rigidbody>(e2);
    scene.assign<gravity>(e3);

    for(auto e: scene.view<rigidbody, transform>()) {
        auto pscale = scene.get<transform>(e);

        printf("scale: %f %f\n", pscale->scale.x, pscale->scale.y);
    }
//    coord.init();
//
//    coord.register_component<gravity>();
//    coord.register_component<rigidbody>();
//    coord.register_component<transform>();
//
//    auto phsystem = coord.register_system<physics_system>();
//
//    ecs::signature sign;
//    sign.set(coord.get_component_type<gravity>());
//    sign.set(coord.get_component_type<rigidbody>());
//    sign.set(coord.get_component_type<transform>());
//    coord.set_system_signature<physics_system>(sign);
//
//    mem::vector<ecs::entity> entities;
//    entities.reserve(ecs::MAX_ENTITIES);
//
//    ecs::entity e = coord.create_entity();
//
//    coord.add_component(e, gravity {vec2f {1.f, 2.f}});
//    coord.add_component(e, rigidbody {vec2f {1.f, 2.f}});
//    coord.add_component(e, transform {vec2f {1.f, 2.f}});
//
//    phsystem->update();

//    recti viewport {0, 0, 160, 144};
//
//    engine::init();
//    window::create(
//        "Pocket Engine",
//        viewport.size() * ZOOM_LEVEL
//    );
//    gfx::init();
//    input::init();
//    window::vsync_on(true);
//
//    mat4 ortho;
//    math::orthographic(
//        ortho,
//        viewport.w, 0.f,
//        0.f,    viewport.h,
//        -1.f,  1.f
//    );
//
//    gfx::sprite spr;
//    spr.texture.load("assets/walking_basic.png");
//    spr.frame = {0.0f, 0.0f, 17.f, 26.f};
//    spr.tex_coords = {0.f, 0.f, 1/12.f, 1.f};
//    spr.offset_center = {0.f, 10.f};
//
//    spr.frame.x = -8.f;
//    spr.frame.y = -8.f;
////    spr.frame.y = 5.f * 16.f;
//
//    vec2f camera_pos {-8.f, -16.f};
//
//    f32 speed = 1.f;
//
//    gfx::tilemap tm;
//    tm.load("assets/map.json");
//
//    gfx::batcher batch;
//
////    window::wireframe_on(true);
//
//    gfx::basic_shader.use();
//    gfx::basic_shader.set("projection", ortho);
//    f32 angle = 0;
//    while(true) {
//        engine::manage_events();
//
//        f32 mov_x = input::is_key_down(SDL_SCANCODE_RIGHT) - input::is_key_down(SDL_SCANCODE_LEFT);
//        f32 mov_y = input::is_key_down(SDL_SCANCODE_DOWN)  -  input::is_key_down(SDL_SCANCODE_UP);
//
//        camera_pos -= { mov_x, mov_y };
//
//        window::clear();
//
//        batch.push_matrix(mat3x2::from_position(camera_pos));
//            batch.set_texture(tm.texture);
//            for(size_t i=0; i<1; i++)
//                for(size_t j=0; j<tm.layers[i].frames.size(); j++)
//                    batch.rect(tm.layers[i].frames[j], tm.layers[i].texcoords[j]);
//        batch.pop_matrix();
//
//        batch.push_matrix(mat3x2::from_position(viewport.size()/2.f));
//            batch.set_texture(spr.texture);
//            batch.rect(spr.frame - spr.offset_center, spr.tex_coords);
//        batch.pop_matrix();
//
//        batch.push_matrix(mat3x2::from_position(camera_pos));
//            batch.set_texture(tm.texture);
//            for(size_t i=1; i<tm.layers.size(); i++)
//                for(size_t j=0; j<tm.layers[i].frames.size(); j++)
//                    batch.rect(tm.layers[i].frames[j], tm.layers[i].texcoords[j]);
//        batch.pop_matrix();
//
//
//
//        batch.render();
//        batch.clear();
//
//        window::swap_buffers();
//    }
}