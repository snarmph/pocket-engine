#include "window.hpp"

#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <SDL2/SDL_opengl.h>

namespace {
    SDL_Window *w;
} // namespace


namespace window {
    const char *name;
    // vec2i position;
    vec2i size;

    void create(const char *name, const vec2i &size) {
        w = SDL_CreateWindow(
            name,
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            size.x, size.y,
            SDL_WINDOW_OPENGL
        );
    }

    void destroy() {
        
    }
} // namespace window