#pragma once
#include <pocket/core/world.hpp>
#include <pocket/math/rect.hpp>
#include "tilemap.hpp"

namespace pk {
    struct map_manager : public component {
        //void awake() override;
        void load(const string &data);
        void unload();

        void update() override;
        
        //bool is_colliding(vec2f &position);


        vector<entity*> entities;
        /*
        - tilemap
        - list of enitites
        - load / unload
        - 
        */
    };
} // namespace pk 