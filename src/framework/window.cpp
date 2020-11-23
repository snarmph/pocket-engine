#include "window.hpp"

#include <cstring>

#include <glad/glad.h>
#include <GL/gl.h>
#include <SDL2/SDL_opengl.h>

namespace {
    SDL_GLContext context;
} // namespace

namespace window {
    SDL_Window *wnd;

    const char *name;
    vec2i size;

    void create(const char *n, const vec2i &s) {
        name = n;
        size = s;
        wnd = SDL_CreateWindow(
            n,
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            s.x, s.y,
            SDL_WINDOW_OPENGL
        );
        context = SDL_GL_CreateContext(wnd);
        if(!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
            printf("failed to initialize glad\n");
            exit(1);
        }
    }

    void destroy() {
        SDL_DestroyWindow(wnd);
    }

    void swap_buffers() {
        SDL_GL_SwapWindow(wnd);
    }
} // namespace window