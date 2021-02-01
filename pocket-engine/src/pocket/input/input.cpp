#include "input.hpp"

#include <array>

#include <sokol/sokol.h>

#include <pocket/util/pkassert.h>

namespace {
    std::array<bool, SAPP_MAX_KEYCODES> keys;
    std::array<bool, SAPP_MAX_KEYCODES> pressed_keys;
} // namespace

namespace input {
    void init() {
        keys.fill(false);
        pressed_keys.fill(false);
    }

    void set_key_down(i32 key) {
        pkassert(key > 0 && key < SAPP_MAX_KEYCODES, "wrong keycode");
        keys[key] = true;
    }

    void set_key_up(i32 key) {
        pkassert(key > 0 && key < SAPP_MAX_KEYCODES, "wrong keycode");
        keys[key] = false;
        pressed_keys[key] = false;
    }

    bool is_key_down(i32 key) {
        pkassert(key > 0 && key < SAPP_MAX_KEYCODES, "wrong keycode");
        return keys[key];
    }

    bool is_key_pressed(i32 key) {
        pkassert(key > 0 && key < SAPP_MAX_KEYCODES, "wrong keycode");
        if(keys[key] && !pressed_keys[key]) {
            pressed_keys[key] = true;
            return true;
        }
        return false;
    }

} // namespace input