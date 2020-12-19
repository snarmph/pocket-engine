#ifndef POCKET_ENGINE_OTHER_HPP
#define POCKET_ENGINE_OTHER_HPP

#include <bitset>
#include <pocket/types.hpp>
#include <pocket/containers/vector.hpp>

namespace ecs {

    extern int component_counter;
    template<typename T>
    int get_id() {
        // static int only runs once, meaning that
        // it will always be the same for the same
        // templated argument
        static int component_id = component_counter++;
        return component_id;
    }

    typedef u32 entity_index;
    typedef u32 entity_version;
    typedef u64 entity;

    inline entity create_entity_id(entity_index index, entity_version version) {
        // shift the index up 32 bits and put the version at the bottom
        return ((entity)index << 32) | ((entity)version);
    }

    inline entity_index get_entity_index(entity id) {
        // shift down 32 so we lose the version
        return id >> 32;
    }

    inline entity_version get_entity_version(entity id) {
        // cast to a 32 bit uint to get version number
        return (entity_version)id;
    }

    inline bool is_entity_valid(entity id) {
        return (id >> 32) != entity_index(-1);
    }

#define INVALID_ENTITY create_entity_id(entity_index(-1), 0)

    const int MAX_COMPONENTS = 32;
    const int MAX_ENTITIES = 500;
    typedef std::bitset<MAX_COMPONENTS> component_mask;

    struct component_pool {
        component_pool(size_t elementsize) {
            element_size = elementsize;
            pdata = new char[elementsize * MAX_ENTITIES];
        }

        ~component_pool() {
            delete[] pdata;
        }

        inline void *get(size_t index) {
            return pdata + index * element_size;
        }

    private:
        char *pdata = nullptr;
        size_t element_size = 0;
    };

    struct scene {
        entity new_entity() {
            assert(entities.size() < MAX_ENTITIES && "max number of entities reached");
            if(!free_entities.empty()) {
                entity_index new_index = free_entities.pop();
                entity new_id = create_entity_id(new_index, get_entity_version(entities[new_index].id));
                entities[new_index].id = new_id;
                return new_id;
            }

            entities.emplace_back(create_entity_id(entity_index(entities.size()), 0), component_mask());
            return entities.back().id;
        }

        template<typename T>
        T *get(entity id) {
            int component_id = get_id<T>();
            if(!entities[get_entity_index(id)].mask.test(component_id))
                return nullptr;
            T *pcomponent = static_cast<T*>(component_pools[component_id]->get(get_entity_index(id)));
            return pcomponent;
        }

        template<typename T>
        T *assign(entity id) {
            int component_id = get_id<T>();

            // not enough component pools
            if(component_pools.size() <= component_id) {
                component_pools.resize(component_id + 1);
            }
            // new pool
            if(component_pools[component_id] == nullptr) {
                component_pools[component_id] = new component_pool(sizeof(T));
            }

            // get the pool at the component id -> get the entity position -> construct
            T *pcomponent = new (component_pools[component_id]->get(get_entity_index(id))) T();

            entities[get_entity_index(id)].mask.set(component_id);
            return pcomponent;
        }

        template<typename T>
        void remove(entity id) {
            if(entities[get_entity_index(id)].id != id)
                return;

            int component_id = get_id<T>();
            entities[get_entity_index(id)].mask.reset(component_id);
        }

        void destroy_entity(entity id) {
            entity newid = create_entity_id(entity_index(-1), get_entity_version(id) + 1);
            entities[get_entity_index(id)].id = newid;
            entities[get_entity_index(id)].mask.reset();
            free_entities.emplace_back(get_entity_index(id));
        }

        template<typename... componenttypes>
        struct scene_view {
            scene_view(scene &s) : pscene(&s) {
                if(sizeof...(componenttypes) == 0) {
                    all = true;
                }
                else {
                    int component_ids[] = {0, get_id<componenttypes>() ...};
                    for(int i = 1; i < (sizeof...(componenttypes) + 1); i++) {
                        comp_mask.set(component_ids[i]);
                    }
                }
            }

            struct iterator {
                iterator(scene *pscene, entity_index index, component_mask mask, bool all)
                        : pscene(pscene), index(index), mask(mask), all(all) {}

                entity operator*() const {
                    return pscene->entities[index].id;
                }

                bool operator==(const iterator &other) const {
                    return index == other.index || index == pscene->entities.size();
                }

                bool operator!=(const iterator &other) const {
                    return index != other.index || index != pscene->entities.size();
                }

                bool valid_index() {
                    return
                        // it's a valid entity id
                            is_entity_valid(pscene->entities[index].id) &&
                            // and it has a correct component mask
                            (all || mask == (mask & pscene->entities[index].mask));
                }

                iterator &operator++() {
                    do {
                        index++;
                    } while(index < pscene->entities.size() && !valid_index());
                    return *this;
                }

            private:
                entity_index index;
                scene *pscene = nullptr;
                component_mask mask;
                bool all = false;
            };

            const iterator begin() const {
                int first_index = 0;
                while(first_index < pscene->entities.size() &&
                      (comp_mask != (comp_mask & pscene->entities[first_index].mask)
                       || !is_entity_valid(pscene->entities[first_index].id))) {
                    first_index++;
                }
                return iterator(pscene, first_index, comp_mask, all);
            }

            const iterator end() const {
                return iterator(pscene, entity_index(pscene->entities.size()), comp_mask, all);
            }

        private:
            scene *pscene = nullptr;
            component_mask comp_mask;
            bool all = false;
        };

        template<typename... componenttypes>
        scene_view<componenttypes...> view() {
            return scene_view<componenttypes...>(*this);
        }

        struct entity_desc {
            entity id;
            component_mask mask;
            entity_desc(entity _id, component_mask _mask)
                : id(_id), mask(_mask) {}
        };
        mem::vector<entity_desc> entities;
        mem::vector<entity_index> free_entities;
        mem::vector<component_pool*> component_pools;
    };

} // namespace ecs

#endif //POCKET_ENGINE_OTHER_HPP
