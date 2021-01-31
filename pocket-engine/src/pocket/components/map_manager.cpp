#include "map_manager.hpp"

#include <algorithm>

#include <pocket/json/json.hpp>
#include <pocket/core/factory.hpp>

#include "tilemap_animator.hpp"
#include "sprite.hpp"
#include "collider.hpp"

namespace pk {
    void map_manager::load(const string &data) {
        // data/maps/pallet-town
        json::Parser ps;
        auto m = ps.parse(json::fromFile(data.stdstr()));

        name = m["name"].as_string();

        entref->add<tilemap_animator>();
        auto tm = entref->add<tilemap>();
        tm->load(m["tilemap"].as_string().c_str());

        tm->position.x = (f32)m["position"]["x"].as_number() * tm->width * tm->tile_size;
        tm->position.y = (f32)m["position"]["y"].as_number() * tm->height * tm->tile_size;

        printf("tm position: %f %f\n", tm->position.x, tm->position.y);

        auto es = m["entities"].as_array();

        if (m["is_first"].as_bool()) {
            entities.emplace_back(factory::new_player("data/player/data.json"));
            factory::get_world().set_map(this);
        }

        for (auto ent : es) {
            f32 posx = ent["position"]["x"].cast<u32>() * tm->tile_size;
            f32 posy = ent["position"]["y"].cast<u32>() * tm->tile_size;
            posx += tm->position.x;
            posy += tm->position.y;
            printf("position: %f %f\n", posx, posy);
            entities.emplace_back(factory::new_gameobject({ posx, posy }));
        }
    }

    void map_manager::unload() {

    }

    void map_manager::update() {
    }

    bool map_manager::is_inside(const vec2f &pos) {
        return get<tilemap>()->position_to_index(pos) != -1;
    }
    bool map_manager::is_colliding(const vec2f &pos) {
        auto tm = get<tilemap>();
        i32 index = tm->position_to_index(pos);
        // if it's inside the tilemap
        if (index != -1) {
            if (tm->is_colliding(index))
                return true;
            for (auto &e : entities) {
                if (e->comps[0]->position == pos) {
                    return e->has<collider>();
                }
            }
        }
        return false;
    }


} // namespace pk