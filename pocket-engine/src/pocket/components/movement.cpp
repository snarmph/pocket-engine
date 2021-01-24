#include "movement.hpp"

#include <pocket/core/types.hpp>
#include <pocket/core/time.hpp>
#include <pocket/input/input.hpp>
#include <pocket/math/vecmath.hpp>

#include "sprite.hpp"
#include "tilemap.hpp"

namespace {
    constexpr f32 base_speed = 20.f;
} // namespace

namespace pk {
    void movement::awake() {
        mov_dir = vec2f::zero();
        new_pos = position;
    }

    void movement::update() {
        if (!finished()) {
            entref->worldref->update_sorting = true;
            f32 vel = speed * base_speed * time::dt;
            position += mov_dir * vel;
            f32 dist2 = powf(new_pos.x - position.x, 2) + powf(new_pos.y - position.y, 2);
            if (dist2 <= (vel * vel)) {
                current_path ++;
                position = new_pos;
                position = new_pos;
                // if finished the paths
                if (current_path == path.size()) {
                    path.clear();
                    current_path = 0;
                }
                // next path
                else {
                    next_path();
                }
            }
            for (auto comp : entref->comps)
                if (comp != this)
                    comp->position = position;
        }
    }

    void movement::add_path(const vec2i &dir) {
        if (math::mag2(dir) > 1) {
            i32 absx = abs(dir.x);
            i32 absy = abs(dir.y);
            i32 ntimes = (absx > absy) ? absx : absy;
            vec2i newdir = dir / ntimes;
            for (i32 i = 0; i < ntimes; i++)
                add_path(newdir);
        }
        else {
            //path.emplace_back(dir);
            path.emplace_back(dir_from_vec2i(dir));
        }
        // if it's the first path added
        if (path.size() == 1)
            next_path();
    }

    void movement::add_path(i32 x, i32 y) {
        add_path({ x, y });
    }

    void movement::add_path(directions dir) {
        switch (dir) {
            case pk::directions::north:
                add_path({ 0, -1 });
                break;
            case pk::directions::south:
                add_path({ 0, 1 });
                break;
            case pk::directions::east:
                add_path({ -1, 0 });
                break;
            case pk::directions::west:
                add_path({ 1, 0 });
                break;
            case pk::directions::error:
            default:
                assert(false && "directions should not be error");
                break;
        }
    }

    void movement::next_path() {
        mov_dir = vec2i_from_dir(path[current_path]);
        new_pos = position + (mov_dir * 16.f);
        last_direction = get_direction();

        auto tm = entref->worldref->get_first<tilemap>();
        i32 index = tm->position_to_index(new_pos);
        if (index == -1)
            return;

        if (tm->is_colliding(index)) {
            new_pos = position;
            current_path++;
            // if finished the paths
            if (current_path == path.size()) {
                path.clear();
                current_path = 0;
            }
            // next path
            else {
                next_path();
            }
        }
    }

    bool movement::finished() {
        return path.size() == 0;
    }

} // namespace pk