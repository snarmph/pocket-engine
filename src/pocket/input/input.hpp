#ifndef INPUT_HPP
#define INPUT_HPP

#include <pocket/types.hpp>

namespace input {
    void init();
    void set_key_down(i32 key);
    void set_key_up(i32 key);
    bool is_key_down(i32 key);
    bool is_key_pressed(i32 key);
} // namespace input

#endif