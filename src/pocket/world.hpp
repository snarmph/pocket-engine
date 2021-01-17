#pragma once
#include <iostream>
#include <array>
#include <cstdio>
#include <tuple>
#include <pocket/containers/vector.hpp>
#include <pocket/math/vec.hpp>
#include <pocket/graphics/batch.hpp>
#include <pocket/util/pkassert.h>

namespace pk {
    struct world;
    struct entity;
    struct component;

    using std::array;
    using mem::vector;

    struct types {
    private:
        static inline uint8_t counter = 0;
    public:
        static uint8_t count() { 
            return counter; 
        }

        template<typename T>
        static uint8_t id() {
            static const uint8_t value = counter++;
            return value;
        }
    };

    struct component {
        uint8_t id = 0;

        entity *entref = nullptr;

        bool active = true;
        bool visible = true;

        vec2f position;

        virtual void awake();
        virtual void update();
        virtual void render(gfx::batcher &batch);
    };

    struct entity {
        vector<component*> comps;
        bool active = true;
        bool visible = true;
        world *worldref = nullptr;

        template<typename T>
        T *get();

        template<typename T>
        T *add();
    };

    struct world {
        ~world();

        entity *new_entity();

        template<typename T>
        T *add(entity *e);

        void destroy_entity(entity *e);
        void destroy_entity(entity *e, size_t index);

        void destroy_component(component *c);
        void destroy_component(component *c, size_t index);

        void update();
        void render(gfx::batcher &batch);

        array<vector<component*>, 100> comps_cache;
        array<vector<component*>, 100> comps_alive;
        vector<entity*> ents_cache;
        vector<entity*> ents_alive;
    };

    // declarations
    template<typename T>
    T *entity::get() {
        for(auto &c: comps)
            if(c->id == types::id<T>())
                return (T*)c;
        pkassert(false, "didn't find entity");
    }

    template<typename T>
    T *entity::add() {
        return worldref->add<T>(this);
    }

    template<typename T>
    T *world::add(entity *e) {
        auto id = types::id<T>();
        auto &cache = comps_cache[id];
        auto &alive = comps_alive[id];

        T *instance;
        if(cache.size() > 0) {
            instance = (T*)cache.back();
            cache.erase(cache.size()-1);
        }
        else {
            instance = new T();
        }

        instance->id = id;
        instance->entref = e;

        alive.emplace_back(instance);

        e->comps.emplace_back(instance);
            
        instance->awake();
        return instance;
        /*
        uint8_t id = types::id<T>();
        auto &alive = comps_alive[id];

        T *instance;
        if(comp_current >= comp_pool.size()) {
            printf("adding to the back\n");
            comp_pool.emplace_back();
            instance = comp_pool.back().ref();
        }
        else {
            instance = comp_pool[comp_current].ref();
        }
        comp_current++;

        instance->id = id;
        instance->entref = e;
        instance->active = true;

        for(auto &alive: comps_alive) {
            for(component *c: alive) {
                printf("id>> > %u\n", c->id);
            }
        }

        alive.emplace_back(instance);

        for(auto &alive: comps_alive) {
            for(component *c: alive) {
                printf("id>>> %u\n", c->id);
            }
        }


        e->comps.emplace_back(instance);
            
        instance->awake();
        return instance;
        */
    }


} // namespace pk

