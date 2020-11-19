#include <cstdio>
#include <cstdbool>

#include "framework/engine.hpp"
#include "framework/window.hpp"
#include "framework/input.hpp"

int main() {
    engine::init();
    input::init();
    window::create(
        "Pocket Engine", 
        {500, 500}
    );

    while(true) {
        engine::manage_events();
    }

}