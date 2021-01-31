#include "player_controller.hpp"

#include <pocket/core/types.hpp>
#include <pocket/core/time.hpp>
#include <pocket/input/input.hpp>
#include <pocket/math/vecmath.hpp>

#include "animator.hpp"
#include "sprite.hpp"
#include "map_manager.hpp"
#include "collider.hpp"

namespace pk {
    void player_controller::awake() {
        auto spr = get<sprite>();
        auto mov = get<movement>();

        local_center = spr->frame.size() / 2.f;
        spr->offset.x = spr->frame.w - 16.f;
        spr->offset.y = spr->frame.h - 16.f;

        position.x = (16.f * 10);
        position.y = (16.f * 10);

        spr->position = position;
        mov->position = position;
    }

    using input::is_key_down;
    using input::is_key_pressed;

    void player_controller::update() {
        auto mov = get<movement>();
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
                // remove diagonal movement
                input_dir.x = (input_dir.y) ? 0 : input_dir.x;

                // if it's looking in a different direction then what pressed
                if (input_dir != vec2i_from_dir(mov->last_direction)) {
                    // get the looking direction and set the animation
                    mov->turn(input_dir);
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

                /*
                * check that the player is still inside the map
                * if its not, check all the maps and find the one its inside
                */
                if (!check_map_change())
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
            // check that's still moving
            is_moving = !mov->finished();
            if (!is_moving)
                was_moving = true;
        }

        old_input_dir = input_dir;
    }

    bool player_controller::check_map_change() {
        vec2f new_pos = position + input_dir * 16.f;

        map_manager *mm = entref->worldref->get_map();
        if (mm->is_inside(new_pos))
            return false;

        auto &all_maps = entref->worldref->get_all<map_manager>();
        for (component *m : all_maps) {
            map_manager *current = (map_manager *)m;
            // if its the current map, skip
            if (current == mm)
                continue;
            if (current->is_inside(new_pos)) {
                if (current->is_colliding(new_pos)) {
                    get<movement>()->turn(input_dir);
                    input_dir = vec2i::zero();
                    return true;
                }
                printf("entering %s\n", current->name.cstr());
                entref->worldref->set_map(current);
                return true;
            }
        }

        pkassert(false, "player moved outside of any map");
        return false;
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