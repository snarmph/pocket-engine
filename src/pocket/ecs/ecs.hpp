#ifndef POCKET_ENGINE_ECS_HPP
#define POCKET_ENGINE_ECS_HPP

#include <bitset>
#include <queue>
#include <array>
#include <cassert>
#include <unordered_map>
#include <typeinfo>
#include <memory>
#include <set>

#include <pocket/types.hpp>
#include <pocket/containers/vector.hpp>

namespace ecs {
    using entity = u32;
    const entity MAX_ENTITIES = 5000;

    using component_type = u8;
    const component_type MAX_COMPONENTS = 32;

    using signature = std::bitset<MAX_COMPONENTS>;

    struct entity_manager {
        entity_manager() {
            for(entity e=0; e<MAX_ENTITIES; e++) {
                avaiable_entities.emplace_back(e);
            }
        }

        entity create_entity() {
            assert(living_entity_count < MAX_ENTITIES && "too many entities in existence");

            living_entity_count++;
            return avaiable_entities.pop();
        }

        void destroy_entity(entity e) {
            assert(e < MAX_ENTITIES && "entity out of range");
            signatures[e].reset();
            avaiable_entities.emplace_back(e);
            living_entity_count--;
        }

        void set_signature(entity e, signature s) {
            assert(e < MAX_ENTITIES && "entity out of range");

            signatures[e] = s;
        }

        signature get_signature(entity e) {
            assert(e < MAX_ENTITIES && "entity out of range");

            return signatures[e];
        }

    private:
        mem::vector<entity> avaiable_entities;
        std::array<signature, MAX_ENTITIES> signatures;
        u32 living_entity_count = 0;
    };

    struct Icomponent_array {
        virtual ~Icomponent_array() = default;
        virtual void entity_destroyed(entity e) = 0;
    };

    template<typename T>
    struct component_array : public Icomponent_array {
        void insert_data(entity e, T component) {
            assert(entity_to_index.find(e) == entity_to_index.end() && "component added to same entity more than once");

            size_t new_index = arr_size;
            entity_to_index[e] = new_index;
            index_to_entity[new_index] = e;
            component_array[new_index] = component;
            arr_size++;
        }

        void remove_data(entity e) {
            assert(entity_to_index.find(e) != entity_to_index.end() && "removing non-existent component");

            size_t index_of_removed = entity_to_index[e];
            size_t index_of_last = arr_size - 1;
            component_array[index_of_removed] = component_array[index_of_last];

            entity ent_of_last_elem = index_to_entity[index_of_last];
            entity_to_index[ent_of_last_elem] = index_of_removed;
            index_to_entity[index_of_removed] = ent_of_last_elem;

            entity_to_index.erase(e);
            index_to_entity.erase(index_of_last);

            arr_size--;
        }

        T &get_data(entity e) {
            assert(entity_to_index.find(e) != entity_to_index.end() && "accessing non-existent component");

            return component_array[entity_to_index[e]];
        }

        void entity_destroyed(entity e) override {
            if(entity_to_index.find(e) != entity_to_index.end()) {
                remove_data(e);
            }
        }

    private:
        std::array<T, MAX_ENTITIES> component_array;
        std::unordered_map<entity, size_t> entity_to_index;
        std::unordered_map<size_t, entity> index_to_entity;

        size_t arr_size = 0;
    };

    struct component_manager {
        template<typename T>
        void register_component() {
            const char *type_name = typeid(T).name();

            assert(component_types.find(type_name) == component_types.end() && "registering component type more than once.");

            component_types.insert({type_name, next_component_type});

            component_arrays.insert({type_name, std::make_shared<component_array<T>>()});

            next_component_type++;
        }

        template<typename T>
        component_type  get_component_type() {
            const char *type_name = typeid(T).name();
            assert(component_types.find(type_name) != component_types.end() && "component not registered before use");

            return component_types[type_name];
        }

        template<typename T>
        void add_component(entity e, T component) {
            get_component_array<T>()->insert_data(e, component);
        }

        template<typename T, typename ... Ts>
        void emplace_component(entity e, Ts... args) {

        }

        template<typename T>
        void remove_component(entity e) {
            get_component_array<T>()->remove_data(e);
        }

        template<typename T>
        T &get_component(entity e) {
            return get_component_array<T>()->get_data(e);
        }

        void entity_destroyed(entity e) {
            for(const auto &pair: component_arrays) {
                auto const &component = pair.second;
                component->entity_destroyed(e);
            }
        }

    private:
        std::unordered_map<const char*, component_type> component_types {};
        std::unordered_map<const char*, std::shared_ptr<Icomponent_array>> component_arrays {};

        component_type next_component_type {};

        template<typename T>
        std::shared_ptr<component_array<T>> get_component_array() {
            const char *type_name = typeid(T).name();
            assert(component_types.find(type_name) != component_types.end() && "component not registered before use");

            return std::static_pointer_cast<component_array<T>>(component_arrays[type_name]);
        }
    };

    struct system {
        std::set<entity> entities;
    };

    struct system_manager {
        template<typename T>
        std::shared_ptr<T> register_system() {
            const char *type_name = typeid(T).name();
            assert(systems.find(type_name) == systems.end() && "registering system more than once");

            auto sys = std::make_shared<T>();
            systems.insert({type_name, sys});
            return sys;
        }

        template<typename T>
        void set_signature(signature s) {
            const char *type_name = typeid(T).name();
            assert(systems.find(type_name) != systems.end() && "system used before registered");

            signatures.insert({type_name, s});
        }

        void entity_destroyed(entity e) {
            for(const auto &pair: systems) {
                const auto &sys = pair.second;
                sys->entities.erase(e);
            }
        }

        void entity_signature_changed(entity e, signature s) {
            for(const auto &pair: systems) {
                const auto &type = pair.first;
                const auto &sys = pair.second;
                const auto &sys_sign = signatures[type];

                if((s & sys_sign) == sys_sign)
                    sys->entities.insert(e);
                else
                    sys->entities.erase(e);
            }
        }


    private:
        std::unordered_map<const char*, signature> signatures;
        std::unordered_map<const char*, std::shared_ptr<system>> systems;
    };

    struct coordinator {
        void init() {
            comp_manag = std::make_unique<component_manager>();
            entity_manag = std::make_unique<entity_manager>();
            system_manag = std::make_unique<system_manager>();
        }

        entity create_entity() {
            return entity_manag->create_entity();
        }

        void destroy_entity(entity e) {
            entity_manag->destroy_entity(e);
        }

        template<typename T>
        void register_component() {
            comp_manag->register_component<T>();
        }

        template<typename T>
        void add_component(entity e, T component) {
            comp_manag->add_component<T>(e, component);
            auto sign = entity_manag->get_signature(e);
            sign.set(comp_manag->get_component_type<T>(), true);
            entity_manag->set_signature(e, sign);

            system_manag->entity_signature_changed(e, sign);
        }

        template<typename T, typename ... Ts>
        void emplace(entity e, Ts... args) {

        }

        template<typename T>
        T &get_component(entity e) {
            return comp_manag->get_component<T>(e);
        }

        template<typename T>
        component_type get_component_type() {
            return comp_manag->get_component_type<T>();
        }

        template<typename T>
        std::shared_ptr<T> register_system() {
            return system_manag->register_system<T>();
        }

        template<typename T>
        void set_system_signature(signature s) {
            system_manag->set_signature<T>(s);
        }

    private:
        std::unique_ptr<component_manager> comp_manag;
        std::unique_ptr<entity_manager> entity_manag;
        std::unique_ptr<system_manager> system_manag;
    };
}

#endif //POCKET_ENGINE_ECS_HPP