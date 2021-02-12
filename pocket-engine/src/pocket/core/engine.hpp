#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <pocket/math/vec.hpp>
#include <pocket/containers/containers.hpp>

#include "types.hpp"

namespace engine {
    struct options {
        vec2i resolution;
        u32 zoom = 1;
        string name;
        bool fullscreen = false;
    };

    void init(options &opts);

    u64 get_ticks();
} // namespace engine

#endif