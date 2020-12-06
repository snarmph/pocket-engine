#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "types.hpp"

namespace engine {
    void init();
    void quit();

    u32 get_ticks();

    void manage_events();
} // namespace engine

#endif