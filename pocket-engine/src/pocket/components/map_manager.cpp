#include "map_manager.hpp"

#include <algorithm>

#include <pocket/json/json.hpp>
#include <pocket/core/factory.hpp>

#include "tilemap_animator.hpp"
#include "sprite.hpp"

//#include<pocket/generated/tileset_data.hpp>

namespace pk {
    void map_manager::load(const string &data) {
        // data/maps/pallet-town
        json::Parser ps;
        auto m = ps.parse(json::fromFile(data.stdstr()));
        //auto tm = factory::new_tilemap(m["tilemap"].as_string().c_str());
        entref->add<tilemap_animator>();
        auto tm = entref->add<tilemap>();
        tm->load(m["tilemap"].as_string().c_str());
    
        auto es = m["entities"].as_array();

        entities.emplace_back(factory::new_player("data/player/data.json"));

        for (auto ent : es) {
            f32 posx = ent["position"]["x"].cast<u32>() * tm->tile_size;
            f32 posy = ent["position"]["y"].cast<u32>() * tm->tile_size;
            printf("position: %f %f\n", posx, posy);
            entities.emplace_back(factory::new_gameobject({ posx, posy }));
        }
    }

    void map_manager::unload() {

    }

    void map_manager::update() {
        std::sort(
            entities.begin(), 
            entities.end(), 
            [](entity *first, entity *second) {
                return first->comps[0]->position.y < second->comps[0]->position.y;
            });
    }


} // namespace pk