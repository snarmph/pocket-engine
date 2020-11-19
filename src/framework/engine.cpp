#include "engine.hpp"

#include <SDL2/SDL.h>

#include "window.hpp"
#include "input.hpp"

namespace engine {
    void init() {
        SDL_Init(SDL_INIT_EVERYTHING);
    }
    
    void quit() {
        window::destroy();
        SDL_Quit();
        exit(0);
    }

    void manage_events() {
        SDL_Event e;

        while(SDL_PollEvent(&e)) {
            switch(e.type) {
            case SDL_KEYDOWN:
                input::set_key_down(e.key.keysym.scancode);
                break;
                break;
            case SDL_KEYUP:
                input::set_key_up(e.key.keysym.scancode);
                break;
            case SDL_QUIT:
                engine::quit();
                break;
            }
        }
    }

} // namespace engine