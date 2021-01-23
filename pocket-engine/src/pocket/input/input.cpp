#include "input.hpp"

#include <array>

#include <pocket/util/pkassert.h>

namespace {
    std::array<bool, SDL_NUM_SCANCODES> keys;
    std::array<bool, SDL_NUM_SCANCODES> pressed_keys;
} // namespace

namespace input {
    void init() {
        keys.fill(false);
        pressed_keys.fill(false);
    }

    void set_key_down(i32 key) {
        pkassert(key>0 && key<SDL_NUM_SCANCODES, "wrong keycode");
        keys[key] = true;
    }

    void set_key_up(i32 key) {
        pkassert(key>0 && key<SDL_NUM_SCANCODES, "wrong keycode");
        keys[key] = false;
        pressed_keys[key] = false;
    }

    bool is_key_down(i32 key) {
        pkassert(key>0 && key<SDL_NUM_SCANCODES, "wrong keycode");
        return keys[key];
    }

    bool is_key_pressed(i32 key) {
        pkassert(key>0 && key<SDL_NUM_SCANCODES, "wrong keycode");
        if(keys[key] && !pressed_keys[key]) {
            pressed_keys[key] = true;
            return true;
        }
        return false;
    }

} // namespace input