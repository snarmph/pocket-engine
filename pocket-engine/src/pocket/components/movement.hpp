#pragma once
#include <pocket/core/world.hpp>
#include <pocket/containers/containers.hpp>

namespace pk {
    enum class directions : u8 {
        north, south, east, west, error
    };

    inline directions dir_from_vec2i(const vec2i &dir);
    inline vec2i vec2i_from_dir(const directions dir);

	struct movement : public component {
        void awake() override;
        void update() override;

        void add_path(const vec2i &p);
        void add_path(i32 x, i32 y);
        void add_path(directions dir);
        void next_path();

        bool finished();

        inline directions get_direction();

        directions last_direction = directions::south;
        f32 speed = 3.f;
    private:
        bool is_moving = false;
        vector<directions> path;
        u32 current_path = 0;

        vec2i input_dir;
        vec2f mov_dir;
        vec2f new_pos;
	};
    
    directions dir_from_vec2i(const vec2i &dir) {
        switch (dir.x) {
        case -1: return directions::east;
        case 1:  return directions::west;
        }
        switch (dir.y) {
        case -1: return directions::north;
        case 1:  return directions::south;
        }
        return directions::error;
    }

    vec2i vec2i_from_dir(const directions dir) {
        switch (dir) {
        case directions::north:
            return {0, -1};
            break;
        case directions::south:
            return { 0, 1 };
            break;
        case directions::east:
            return { -1, 0 };
            break;
        case directions::west:
            return { 1, 0 };
            break;
        default:
            assert(false && "wrong direction given");
            // return random value just to remove warning
            return { -1, -1 };
            break;
        }
    }

    inline directions movement::get_direction() {
        return path[current_path];
    }
} // namespace pk

