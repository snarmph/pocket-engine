#include "engine.hpp"

#include <SDL2/SDL.h>
#include <GL/gl.h>

#include "window.hpp"
#include <pocket/input/input.hpp>

namespace engine {
    void init() {
        SDL_Init(SDL_INIT_EVERYTHING);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    }
    
    void quit() {
        window::destroy();
        SDL_Quit();
        exit(0);
    }

    u32 get_ticks() {
        return SDL_GetTicks();
    }

    void manage_events() {
        SDL_Event e;

        while(SDL_PollEvent(&e)) {
            switch(e.type) {
            case SDL_KEYDOWN:
                input::set_key_down(e.key.keysym.scancode);
                break;
            case SDL_KEYUP:
                input::set_key_up(e.key.keysym.scancode);
                break;
            case SDL_QUIT:
                engine::quit();
                break;
            }
        }

        if(input::is_key_pressed(SDL_SCANCODE_ESCAPE))
            engine::quit();
    }

} // namespace engine