#pragma once
#include <iostream>
#include <array>
#include <cstdio>
#include <tuple>
#include <pocket/containers/containers.hpp>
#include <pocket/math/vec.hpp>
#include <pocket/graphics/batch.hpp>
#include <pocket/util/pkassert.h>

namespace pk {
    struct world;
    struct entity;
    struct component;

    struct map_manager;

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

        template<typename T>
        inline T *get();
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

        template<typename T>
        bool has();
    };

    struct world {
        ~world();

        entity *new_entity();

        template<typename T>
        T *add(entity *e);

        template<typename T>
        T *get_first();

        template<typename T>
        vector<component*> &get_all();

        void set_map(map_manager *m);
        map_manager *get_map();

        void destroy_entity(entity *e);
        void destroy_entity(entity *e, size_t index);

        void destroy_component(component *c);
        void destroy_component(component *c, size_t index);

        void update();
        void render(gfx::batcher &batch);

        bool update_sorting = false;
    private:
        //array<vector<component*>, 100> comps_cache;
        //array<vector<component*>, 100> comps_alive;
        vector<vector<component*>> comps_cache;
        vector<vector<component*>> comps_alive;
        vector<entity*> ents_cache;
        vector<entity*> ents_alive;
        map_manager *current_map = nullptr;
        
        vector<component *> &get_cache(uint8_t id) {
            if (id >= comps_cache.size())
                comps_cache.emplace_back();
            pkassert(id < comps_cache.size(), "the id is bigger then the cache size");
            return comps_cache[id];
        }

        vector<component *> &get_alive(uint8_t id) {
            if (id >= comps_alive.size())
                comps_alive.emplace_back();
            pkassert(id < comps_alive.size(), "the id is bigger then the alive size");
            return comps_alive[id];
        }
    };

    // declarations
    template<typename T>
    T *component::get() {
        return entref->get<T>();
    }

    template<typename T>
    T *entity::get() {
        for(auto &c: comps)
            if(c->id == types::id<T>())
                return (T*)c;
        pkassert(false, "didn't find component in entity");
    }

    template<typename T>
    T *entity::add() {
        return worldref->add<T>(this);
    }

    template<typename T>
    bool entity::has() {
        uint8_t id = types::id<T>();
        for (auto &c : comps)
            if (c->id == id)
                return true;
        return false;
    }

    template<typename T>
    T *world::add(entity *e) {
        auto id = types::id<T>();
        auto &cache = get_cache(id);
        auto &alive = get_alive(id);

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
    }

    template<typename T>
    T *world::get_first() {
        auto id = types::id<T>();
        return (T*)comps_alive[id][0];
    }


    template<typename T>
    vector<component *> &world::get_all() {
        auto id = types::id<T>();
        return comps_alive[id];
    }


} // namespace pk

