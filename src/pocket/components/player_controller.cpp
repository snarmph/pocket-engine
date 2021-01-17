#include "player_controller.hpp"
#include <pocket/types.hpp>
#include <pocket/input/input.hpp>
#include <pocket/math/vecmath.hpp>
#include "sprite.hpp"

extern f32 dt;

namespace pk {
    void player_controller::awake() {
        auto spr = entref->get<sprite>();
        // spr.texture = content::find_texture("walking_basic");
        spr->texture.load("assets/walking_basic.png");
        spr->frame = { 0.f, 0.f, 17.f, 26.f };
        spr->tex_coords = { 0.f, 0.f, 1 / 12.f, 1.f };
        spr->offset_center = (vec2i) spr->frame.size() / 2;

        position.x = 8.f;
        position.y = 19.f;

        old_pos = position;
        new_pos = position;
    }

    using input::is_key_down;

    void player_controller::update() {
        // input
        mov_dir.x = is_key_down(SDL_SCANCODE_RIGHT) - is_key_down(SDL_SCANCODE_LEFT);
        mov_dir.y = is_key_down(SDL_SCANCODE_DOWN) - is_key_down(SDL_SCANCODE_UP);
        if(!is_moving) {
            is_moving = mov_dir.x || mov_dir.y;
            if(is_moving) {
                mov_dir.x = (mov_dir.y) ? 0 : mov_dir.x;
                old_pos = mov_dir;
                new_pos = position + (mov_dir * 16);
            }
        }

        // movement
		if (is_moving) {
            f32 vel = speed * dt;
            position += old_pos * vel;
            position.x = roundf(position.x);
            position.y = roundf(position.y);
            f32 dist2 = powf32(new_pos.x - position.x, 2) + powf32(new_pos.y - position.y, 2);
            if(dist2 <= (vel*vel)) {
                is_moving = false;
                position = new_pos;
            }
            auto &spr_pos = entref->get<sprite>()->position;
            spr_pos.x = roundf(position.x);
            spr_pos.y = roundf(position.y);
		}

    }
} // namespace pk 