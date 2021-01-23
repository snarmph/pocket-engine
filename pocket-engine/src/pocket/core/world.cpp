#include "world.hpp"

namespace pk {
    void component::awake() {}
    void component::update() {}
    void component::render(gfx::batcher &batch) {}

    world::~world() {
        for(i64 i = (i64)(ents_alive.size()) - 1; i >= 0; i--)
            destroy_entity(ents_alive[i], (size_t)i);

        for(auto &cache: comps_cache)
            for(component *c: cache)
                delete c;

        for(entity *e: ents_cache)
            delete e;
    }

    entity *world::new_entity() {
        entity *instance = nullptr;

        if(ents_cache.size() > 0) {
            instance = ents_cache.front();
            ents_cache.erase(0);
            *instance = entity();
        }
        else {
            instance = new entity();
        }

        ents_alive.emplace_back(instance);

        // initialize entity
        instance->worldref = this;

        return instance;
    }

    void world::destroy_entity(entity *e) {
        for(i32 i = (i32)(e->comps.size()) - 1; i >= 0; i--)
            destroy_component(e->comps[i]);

        ents_alive.remove(e);
        ents_cache.emplace_back(e);
    }

    void world::destroy_entity(entity *e, size_t index) {
        for(i32 i = (i32)(e->comps.size()) - 1; i >= 0; i--)
            destroy_component(e->comps[i], i);

        ents_alive.erase(index);
        ents_cache.emplace_back(e);
    }

    void world::destroy_component(component *c) {
        auto id = c->id;

        auto &list = c->entref->comps;
        list.remove(c);

        comps_alive[id].remove(c);
        comps_cache[id].emplace_back(c);
    }

    void world::destroy_component(component *c, size_t index) {
        auto id = c->id;

        auto &list = c->entref->comps;
        list.erase(index);

        comps_alive[id].remove(c);
        comps_cache[id].emplace_back(c);
    }

    void world::update() {
        for(auto &alive: comps_alive) {
            for(component *c: alive) {
                if(c->active)
                    c->update();
            }
        }
    }

    void world::render(gfx::batcher &batch) {
        for(auto &alive: comps_alive) {
            for(component *c: alive) {
                if(c->active)
                    c->render(batch);
            }
        }
    }
} // namespace pk
