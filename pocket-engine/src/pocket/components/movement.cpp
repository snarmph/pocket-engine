#include "movement.hpp"

#include <pocket/core/types.hpp>
#include <pocket/core/time.hpp>
#include <pocket/input/input.hpp>
#include <pocket/math/vecmath.hpp>
#include <pocket/util/pkassert.h>

#include "sprite.hpp"
#include "tilemap.hpp"
#include "map_manager.hpp"

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
        bool is_first_path = path.size() == 0;

        // if its moving more than a single block, add all the movements one by one
        if (math::mag2(dir) > 1) {
            i32 absx = abs(dir.x);
            i32 absy = abs(dir.y);
            i32 ntimes = (absx > absy) ? absx : absy;
            vec2i newdir = dir / ntimes;
            for (i32 i = 0; i < ntimes; i++)
                add_path(newdir);
        }
        else {
            path.emplace_back(dir_from_vec2i(dir));
        }
        // if it's the first path added
        if (is_first_path)
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
                pkassert(false, "directions should not be error");
                break;
        }
    }

    void movement::next_path() {
        mov_dir = vec2i_from_dir(path[current_path]);
        new_pos = position + (mov_dir * 16.f);
        last_direction = get_direction();

        map_manager *mm = entref->worldref->get_map();
        if (mm->is_colliding(new_pos)) {
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

    void movement::turn(const vec2i &p) {
        turn(dir_from_vec2i(p));
    }

    void movement::turn(directions dir) {
        last_direction = dir;
    }

    bool movement::finished() {
        return path.size() == 0;
    }

} // namespace pk