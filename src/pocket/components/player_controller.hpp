#pragma once
#include <pocket/world.hpp>
#include <pocket/math/vec.hpp>

namespace pk {
    struct player_controller : public component {
        void awake() override;
        void update() override;

    private:
        bool is_moving = false;
        f32 speed = 30.f;
        vec2i mov_dir;
        vec2f old_pos;
        vec2f new_pos;
        f32 t;
    };
} // namespace pk