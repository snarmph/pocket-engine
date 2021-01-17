#ifndef INPUT_HPP
#define INPUT_HPP

#include <pocket/types.hpp>
#ifdef __linux__ 
#include <SDL2/SDL.h>
#elif _WIN32
#include <sdl2/include/SDL.h>
#else
#error "PLATFORM NOT SUPPORTED"
#endif

namespace input {
    void init();

    void set_key_down(i32 key);
    void set_key_up(i32 key);
    bool is_key_down(i32 key);
    bool is_key_pressed(i32 key);
} // namespace input

#endif