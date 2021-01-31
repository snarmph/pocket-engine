#pragma once
#include <pocket/core/world.hpp>
#include <pocket/math/rect.hpp>
#include "tilemap.hpp"

namespace pk {
    struct map_manager : public component {
        void load(const string &data);
        void unload();

        void update() override;
        
        bool is_inside(const vec2f &pos);
        bool is_colliding(const vec2f &pos);

        string name = "no name";
        vector<entity*> entities;
    };
} // namespace pk 