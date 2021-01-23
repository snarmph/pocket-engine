#pragma once
#include <pocket/core/world.hpp>
#include <pocket/math/vec.hpp>

#include "movement.hpp"

namespace pk {
    struct player_controller : public component {
        void awake() override;
        void update() override;

    private:
        void set_moving_direction(directions dir);
        void set_idle_direction(directions dir);

        bool is_moving = false;
        bool was_moving = false;
        vec2i input_dir;
        vec2i old_input_dir;
    
        const f32 delay = 0.1f;
        f32 cur_delay = 0.f;
    };
} // namespace pk