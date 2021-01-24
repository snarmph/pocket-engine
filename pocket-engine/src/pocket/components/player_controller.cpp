#include "player_controller.hpp"

#include <pocket/core/types.hpp>
#include <pocket/core/time.hpp>
#include <pocket/input/input.hpp>
#include <pocket/math/vecmath.hpp>

#include "animator.hpp"
#include "sprite.hpp"

namespace pk {
    void player_controller::awake() {
        auto spr = get<sprite>();
        auto anim = get<animator>();
        auto mov = get<movement>();
        // spr.texture = content::find_texture("walking_basic");
        //spr->texture.load("assets/walking_basic.png");
        spr->frame = { 0.f, 0.f, 16.f, 24.f };
        local_center = spr->frame.size() / 2.f;
        spr->offset.y = 8.f;
        //local_center.y -= 8.f;

        position.x = (16.f * 10);
        position.y = (16.f * 10);

        spr->position = position;
        mov->position = position;
    }

    using input::is_key_down;
    using input::is_key_pressed;

    void player_controller::update() {
        auto mov = get<movement>();
        //printf("pos: %f %f\n", position.x, position.y);
        
        // input
        input_dir.x = is_key_down(SDL_SCANCODE_RIGHT) - is_key_down(SDL_SCANCODE_LEFT);
        input_dir.y = is_key_down(SDL_SCANCODE_DOWN) - is_key_down(SDL_SCANCODE_UP);

        // check that its not currently moving
        if(!is_moving) {
            bool should_move = input_dir.x || input_dir.y;
            if (was_moving) {
                is_moving = should_move;
            }
            else if (should_move) {
                // if it's looking in a different direction then what pressed
                if (input_dir != vec2i_from_dir(mov->last_direction)) {
                    // remove diagonal movement
                    input_dir.x = (input_dir.y) ? 0 : input_dir.x;
                    // get the looking direction and set the animation
                    mov->last_direction = dir_from_vec2i(input_dir);
                    set_idle_direction(mov->last_direction);
                    // reset the delay
                    cur_delay = 0.f;
                }
                // if the button has been released, move the character immediately (if the direction is the same)
                else if (old_input_dir == vec2i::zero()) {
                    cur_delay = delay;
                }
                // move the character after a delay
                else {
                    cur_delay += time::dt;
                    if (cur_delay >= delay) {
                        is_moving = should_move;
                        cur_delay = 0.f;
                    }
                }
            }

            if(is_moving) {
                // remove diagonal movement
                input_dir.x = (input_dir.y) ? 0 : input_dir.x;
                mov->add_path(input_dir);
                set_moving_direction(mov->last_direction);
            }
            // if it was moving but now has stopped
            else if (was_moving) {
                was_moving = false;
                set_idle_direction(mov->last_direction);
            }
        }
        
        if (is_moving) {
            vec2f &pos = mov->position;
            // check that's still moving
            is_moving = !mov->finished();
            if (!is_moving) {
                was_moving = true;
            }
        }

        old_input_dir = input_dir;
    }

    const vec2f &player_controller::get_local_center() {
        return local_center;
    }

    vec2f player_controller::get_global_center() {
        return position + local_center;
    }

    void player_controller::set_moving_direction(directions dir) {
        // not particularly clean but pretty fast
        auto anim = get<animator>();
        switch (dir) {
        case directions::north:
            anim->play("walk-up");
            break;
        case directions::south:
            anim->play("walk-down");
            break;
        case directions::east:
            anim->play("walk-left");
            break;
        case directions::west:
            anim->play("walk-right");
            break;
        }
    }

    void player_controller::set_idle_direction(directions dir) {
        auto anim = get<animator>();
        switch (dir) {
        case directions::north:
            anim->play("look-up");
            break;
        case directions::south:
            anim->play("look-down");
            break;
        case directions::east:
            anim->play("look-left");
            break;
        case directions::west:
            anim->play("look-right");
            break;
        }
    }
} // namespace pk 